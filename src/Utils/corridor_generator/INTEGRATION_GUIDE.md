# LV-DOT 与 Corridor Generator 整合指南

## 📝 修改摘要

### 1. 话题连接修复 ✅

**问题**：LV-DOT 和 corridor_generator 的话题名称不匹配
- **LV-DOT 发布**：`/onboard_detector/confirmed_targets`
- **corridor_generator 订阅**：原来是 `/detector/target_boxes`（不匹配❌）

**解决**：已修改 `corridor_generator_node.cpp` 订阅正确的话题：
```cpp
// 修改后（第38行）
target_box_sub_ = nh_.subscribe("/onboard_detector/confirmed_targets", 10, ...);
```

### 2. 坐标系统一 ✅

**问题**：LV-DOT 使用 `map` 坐标系，但项目其他部分使用 `world` 坐标系

**解决**：已将 LV-DOT 中所有可视化输出改为 `world` 坐标系，包括：
- 下采样点云（2处）
- 3D检测框
- 目标ID标签
- 确认目标消息
- 激光雷达聚类

**修改文件**：`onboard_detector/include/onboard_detector/dynamicDetector.cpp`

---

## 🚀 使用方法

### 方法1：使用真实目标检测（LV-DOT）

```bash
# 终端1：启动你的仿真环境（包含点云数据）
roslaunch your_sim simulation.launch

# 终端2：启动 LV-DOT 目标检测
source devel/setup.bash
roslaunch onboard_detector run_detector.launch

# 终端3：启动飞行走廊生成器
source devel/setup.bash
roslaunch corridor_generator corridor_generator.launch
```

### 方法2：使用测试发布器（调试用）

```bash
# 一键启动测试环境（包含模拟目标和走廊生成器）
source devel/setup.bash
roslaunch corridor_generator test_with_target.launch
```

---

## 🔧 话题说明

### LV-DOT 发布的话题

| 话题名称 | 消息类型 | 说明 |
|---------|---------|------|
| `/onboard_detector/confirmed_targets` | `TargetBoxArray` | 确认的目标3D框（多帧融合后） |
| `/onboard_detector/filtered_bboxes` | `MarkerArray` | 过滤后的检测框（可视化） |
| `/onboard_detector/lidar_bboxes` | `MarkerArray` | 原始激光雷达检测框 |
| `/onboard_detector/target_id_labels` | `MarkerArray` | 目标ID标签 |

### Corridor Generator 订阅/发布的话题

**订阅**：
- `/onboard_detector/confirmed_targets` - 目标检测结果（自动模式）
- `/clicked_point` - RViz 点击位置（手动模式）
- `/sdf_map/occupancy_all` - 障碍物点云

**发布**：
- `/corridor_generator/polyhedrons` - 生成的飞行走廊（多面体）
- `/corridor_generator/markers` - 可视化标记
- `/corridor_generator/processed_cloud` - 处理后的点云（调试用）

---

## ⚙️ 参数配置

### Corridor Generator 参数

在 `corridor_generator.launch` 中调整：

```xml
<!-- 走廊膨胀半径 -->
<param name="corridor_radius" value="1.5" type="double"/>

<!-- 局部搜索范围 -->
<param name="local_bbox_x" value="5.0" type="double"/>
<param name="local_bbox_y" value="5.0" type="double"/>
<param name="local_bbox_z" value="3.0" type="double"/>

<!-- 目标框安全裕度（会在目标框周围额外移除点云） -->
<param name="target_bbox_padding" value="0.5" type="double"/>

<!-- 最小地面高度 -->
<param name="min_ground_height" value="0.0" type="double"/>
```

### LV-DOT 参数

在 `cfg/detector_param.yaml` 中调整：

```yaml
# 多帧融合参数
min_detection_frames: 5        # 确认目标所需的最小连续检测帧数
max_miss_frames: 5             # 目标丢失后保留的最大帧数
target_match_IOU: 0.3          # 跨帧匹配目标的IOU阈值
target_merge_distance: 1.0     # 合并附近目标的距离阈值（米）

# 目标尺寸约束
max_object_size: [3.0, 3.0, 2.0]  # 最大对象尺寸 [x, y, z]（米）
```

---

## 🔍 调试技巧

### 1. 检查话题连接

```bash
# 查看 LV-DOT 是否正在发布目标
rostopic hz /onboard_detector/confirmed_targets

# 查看走廊生成器输出
rostopic hz /corridor_generator/polyhedrons

# 查看目标消息内容
rostopic echo /onboard_detector/confirmed_targets
```

### 2. 可视化调试

在 RViz 中添加以下显示项：
- **PointCloud2**: `/sdf_map/occupancy_all` - 障碍物点云
- **PointCloud2**: `/corridor_generator/processed_cloud` - 处理后的点云（目标已移除）
- **MarkerArray**: `/onboard_detector/filtered_bboxes` - 检测到的目标框
- **MarkerArray**: `/corridor_generator/markers` - 生成的飞行走廊
- **MarkerArray**: `/onboard_detector/target_id_labels` - 目标ID标签

### 3. 常见问题

**问题1**：走廊生成器没有反应
- 检查 LV-DOT 是否检测到目标：`rostopic echo /onboard_detector/confirmed_targets`
- 检查点云是否正在发布：`rostopic hz /sdf_map/occupancy_all`

**问题2**：生成的走廊太小/太大
- 调整 `corridor_radius` 参数
- 调整 `local_bbox_*` 参数
- 调整 `obstacle_search_radius` 参数

**问题3**：目标检测不稳定
- 增加 `min_detection_frames`（需要更多帧确认）
- 调整 LV-DOT 的 DBSCAN 参数

---

## 📊 工作流程

```
LV-DOT 检测 → 多帧融合 → 发布确认目标（带ID）
                               ↓
                    Corridor Generator 接收
                               ↓
                    ┌──────── 检查目标ID ────────┐
                    │                            │
                 新目标                      已存在目标
                    │                            │
            生成新走廊              检查位置变化 > 0.3m？
                    │                    │         │
                    │                   是        否
                    │                    │         │
                    │              更新走廊   跳过更新
                    └────────────────────┴─────────┘
                               ↓
                    删除消失目标的走廊
                               ↓
                    发布所有走廊（数量 = 目标数量）
```

---

## ✨ 特性

1. **双模式支持**：
   - 自动模式：通过 LV-DOT 目标检测自动生成走廊
   - 手动模式：在 RViz 中点击位置手动生成

2. **智能走廊管理（基于目标ID）**：
   - 🆕 **根据目标ID管理走廊**：每个目标ID对应唯一的走廊
   - 🆕 **智能更新策略**：
     - 新目标 → 生成新走廊
     - 已存在目标 → 仅在位置变化 > 0.3m 时更新
     - 消失的目标 → 自动删除对应走廊
   - 🆕 **走廊数量 = 目标数量**：始终保持一致
   - 避免重复生成，提高效率

3. **智能点云处理**：
   - 自动移除目标3D框内的点云
   - 支持安全padding（`target_bbox_padding`）
   - 避免目标被当作障碍物

4. **多帧融合**：
   - LV-DOT 使用多帧融合提高检测稳定性
   - 只有确认的目标才会触发走廊生成

5. **坐标系统一**：
   - 所有组件使用 `world` 坐标系
   - 便于与其他模块集成

---

## 📅 更新日志

### 2025-11-14 (最新)
- ✅ **新增基于ID的智能走廊管理**：
  - 每个目标ID对应唯一走廊
  - 智能更新：仅在位置变化 > 0.3m 时更新
  - 自动删除消失目标的走廊
  - 走廊数量始终等于目标数量
- ✅ 修复 Eigen 向量初始化错误（`featureWeights_` 从9个元素改为10个）
- ✅ 修复话题连接（订阅正确的 `/onboard_detector/confirmed_targets`）
- ✅ 统一坐标系（所有 LV-DOT 输出从 `map` 改为 `world`）
- ✅ 编译通过并测试成功

---

## 🎯 下一步

1. 在真实环境中测试 LV-DOT + Corridor Generator 整合
2. 根据实际效果调整参数
3. 考虑添加动态障碍物避障功能
4. 集成到完整的路径规划系统中

---

**编译成功！系统已就绪！** 🎉

