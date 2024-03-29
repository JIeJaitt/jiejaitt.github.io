---
title: osproxy的开源经历
excerpt: 本博客暂不显示摘要，请大家谅解
abbrlink: a27750ff
toc: true
sticky: 9000
date: 2024-03-08 08:57:54
categories: 期末考试
tags: 期末考试
---




## 过期大文件上传链接



核心思想：分片上传完毕之后，标记分片文件为`is_merge=true`，以防止被重复使用。

在大文件分片上传后合并的场景中，"避免文件覆盖"主要关注的是确保新合并的文件不会意外地覆盖已存在的文件，特别是当这些文件使用相同的名称或存储在相同的位置时。

这里的"文件覆盖"可能发生在几个场景中：

1. **相同文件名**：如果系统允许上传的文件使用相同的名称存储在同一个目录下，那么后上传的文件可能会覆盖之前上传的文件。这在没有足够的唯一性保证或命名约束的系统中尤为常见。

2. **合并过程中的重复操作**：在大文件的分片上传并合并的过程中，如果因为某些原因（如重试机制触发）合并操作被重复执行，而合并后的文件又使用了相同的名称或存储位置，这将导致之前合并的文件被新的合并文件覆盖。

3. **版本控制缺失**：在一个没有实现文件版本控制的系统中，新的操作很容易覆盖旧的数据。比如，用户可能希望保留之前上传的文件版本，但系统默认行为是用新上传的文件替换同名文件。

为了避免这种覆盖，系统设计时可以采取以下措施：

- **使用唯一标识符**：为每个上传的文件或文件的每个分片分配一个唯一标识符（如UUID），确保存储时的文件名是唯一的，这样即使是相同名称的文件也能被安全地存储在系统中。

- **实现版本控制**：对于同一文件的不同版本，可以通过版本号或时间戳等信息，将新的文件存储为一个新版本，而不是替换旧文件。

- **检查合并状态**：在执行合并操作之前检查文件或分片的合并状态，确保合并操作不会在文件已经合并的情况下被不必要地重复执行。

- **临时存储区和最终存储区分离**：在合并完成之前，将分片存储在一个临时位置，只有在合并成功后才将合并后的文件移动到最终的存储位置。这有助于防止对正在使用的文件进行覆盖。

通过这些措施，可以有效地防止文件覆盖的问题，确保数据的完整性和系统的可靠性。

下面是具体的代码改动：

```diff
type MultiPartInfo struct {
	ID           int        `gorm:"column:id;primaryKey;not null;autoIncrement;comment:自增ID"`
	StorageUid   int64      `gorm:"column:storage_uid;not null;comment:存储UID"`
	ChunkNum     int        `gorm:"column:chunk_num;not null;comment:分片序号"`
	Bucket       string     `gorm:"column:bucket;not null;comment:桶"`
	StorageName  string     `gorm:"column:storage_name;not null;comment:存储名称"`
	StorageSize  int64      `gorm:"column:storage_size;comment:文件大小"`
	PartFileName string     `gorm:"column:part_file_name;not null;comment:分片文件名称"`
	PartMd5      string     `gorm:"column:part_md5;not null;comment:分片md5"`
	Status       int        `gorm:"column:status;not null;comment:状态信息"`
	CreatedAt    *time.Time `gorm:"column:created_at;not null;comment:创建时间"`
	UpdatedAt    *time.Time `gorm:"column:updated_at;not null;comment:更新时间"`
+	IsMerged     bool       `gorm:"column:is_merged;not null;default:false;comment:是否已合并"`
}
```

修改上传逻辑upload.go：

```diff
+	// 检查是否已存在is_merged=true的情况
+	var mergedCount int64
+	if err := lgDB.Model(&models.MultiPartInfo{}).Where("storage_uid = ? AND is_merged = ?", uid, true).Count(&mergedCount).Error; err != nil {
+		lgLogger.WithContext(c).Error("检查已合并分片失败")
+		web.InternalError(c, "检查已合并分片失败")
+		return
+	}

+	// 如果已有分片被标记为已合并，则处理对应逻辑
+	if mergedCount > 0 {
+		lgLogger.WithContext(c).Info("存在已合并的分片，无需重复处理")
+		// 可以根据实际情况决定是返回错误、提示信息还是其它逻辑处理
+		return
+	}


+	// 文件合并成功后，更新所有相关分片的IsMerged为true
+	if err := repo.NewMultiPartInfoRepo().UpdateIsMergedByStorageUid(lgDB, uid, true); err != nil {
+		lgLogger.WithContext(c).Error("更新分片数据失败")
+		web.InternalError(c, "更新分片数据失败")
+		return
+	}

	// 首次写入redis 元数据和分片信息
	lgRedis := new(plugins.LangGoRedis).NewRedis()
	metaCache, err := repo.NewMetaDataInfoRepo().GetByUid(lgDB, uid)
```

添加新的数据库操作工具函数，修改路径：app/pkg/repo/multipartinfo.go

```go
// UpdateIsMergedByStorageUid 根据storageUid更新IsMerged字段
func (r *multiPartInfoRepo) UpdateIsMergedByStorageUid(db *gorm.DB, uid int64, b bool) error {
	result := db.Model(&models.MultiPartInfo{}).Where("storage_uid = ?", uid).Update("is_merged", b)
	if result.Error != nil {
		return result.Error
	}
	return nil
}
```

这里我的建议是重新建一张表，那么这张表里面存的是文件的UID，就是唯一标识，然后还有一个字段，标识这个文件的标识当前是否有效

有一个问题就是你这里只做了合并时候UID的校验，分片的时候我认为也要做一次校验。如果这个UID已经废弃了，那你分片上传也要告诉他无效，这个流量是不应该，再打到我们的服务器上来。那如果说你仅仅是合并的时候来校验，那可能有很多无效的流量一直在基于这个UID上传分片，那这个问题也要考虑一下

合并的时候做校验，流程是没有问题的，我的建议就是重新再建一张表，这张表标识你的UID是否有效。
这张表呢，你在上传啊，或者是合并的时候，甚至是你生成UID的时候，这张表其实是被频繁使用的。那么这张表，要跟你就是正常的业务表是要分开的，比如文件存储这张表，相当于是你整个文件存储的一张核心表，那么这张表不应该受到其他的一些校验类的信息的影响

总结下来三个点，第一个点是独立建一张表，用来标识UID是否有效；第二个点是上传分片的时候也要去校验一下这个UID是否有效，如果无效就直接返回了；第三个点是合并的时候，校验它是否有效。


另外，生成 UID的时候，我认为这个校验是没有意义的，因为你本身用的是雪花算法，并发量不会达到那么大，这个也是不会重复的，如果做检验也没问题