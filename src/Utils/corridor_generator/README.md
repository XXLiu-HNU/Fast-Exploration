# 飞行走廊生成器 (Flight Corridor Generator)

这个包提供了一个交互式的飞行走廊生成功能，可以在RViz中点击选择位置，自动生成该位置的飞行走廊并可视化。

## 功能特性

- **交互式选点**：在RViz中使用"Publish Point"工具点击任意位置
- **自动生成走廊**：使用DecompROS库的SeedDecomp算法生成安全飞行走廊
- **实时可视化**：生成的飞行走廊会立即在RViz中显示
- **障碍物感知**：从地图点云中提取障碍物信息

## 依赖

- ROS Noetic
- decomp_ros_msgs
- decomp_ros_utils
- PCL (Point Cloud Library)
- Eigen3

## 编译

```bash
cd /home/xingxun/experiment/Fast-Exploration
catkin build corridor_generator
source devel/setup.bash
```

## 使用方法

### 1. 启动节点

```bash
roslaunch corridor_generator corridor_generator.launch
```

### 2. 或者单独运行节点

```bash
# 启动节点
rosrun corridor_generator corridor_generator_node

# 启动RViz
rviz -d $(rospack find corridor_generator)/launch/corridor_generator.rviz
```

### 3. 在RViz中操作

1. 确保地图数据正在发布到 `/map_ros/cloud` 话题
2. 在RViz工具栏中选择 "PublishPoint" 工具
3. 在3D视图中点击任意位置
4. 系统将自动生成并显示该位置的飞行走廊

## 参数配置

可以在launch文件中调整以下参数：

- `corridor_radius` (默认: 1.5): 飞行走廊的膨胀半径
- `local_bbox_x` (默认: 5.0): 局部边界框X方向的半边长
- `local_bbox_y` (默认: 5.0): 局部边界框Y方向的半边长
- `local_bbox_z` (默认: 3.0): 局部边界框Z方向的半边长
- `obstacle_search_radius` (默认: 15.0): 障碍物搜索半径

## 话题

### 订阅的话题

- `/clicked_point` (geometry_msgs/PointStamped): 从RViz接收点击的点
- `/map_ros/cloud` (sensor_msgs/PointCloud2): 障碍物点云数据

### 发布的话题

- `/corridor_generator/polyhedrons` (decomp_ros_msgs/PolyhedronArray): 生成的多面体走廊
- `/corridor_generator/markers` (visualization_msgs/MarkerArray): 可视化标记

## 可视化说明

生成的飞行走廊包含以下可视化元素：

1. **红色球体**：选中的种子点（点击位置）
2. **绿色箭头**：多面体的每个平面及其法向量
3. **蓝色线框**：局部边界框
4. **半透明多面体**（如果使用decomp_rviz_plugins）：实际的飞行走廊

## 示例

```bash
# 1. 启动你的仿真环境或真实系统（确保有点云发布）
roslaunch your_package your_simulation.launch

# 2. 启动飞行走廊生成器
roslaunch corridor_generator corridor_generator.launch

# 3. 在RViz中点击选择位置，查看生成的飞行走廊
```

## 算法原理

本包使用DecompROS库中的SeedDecomp算法：

1. 接收用户点击的种子点
2. 从点云地图中提取种子点附近的障碍物
3. 以种子点为中心，按指定半径膨胀一个球形区域
4. 根据障碍物计算安全的凸多面体飞行走廊
5. 应用局部边界框约束
6. 发布并可视化结果

## 故障排除

**问题：点击后没有反应**
- 检查是否有点云数据发布到 `/map_ros/cloud`
- 查看终端是否有错误信息
- 确认点击的位置在地图范围内

**问题：生成的走廊太小或太大**
- 调整 `corridor_radius` 参数
- 调整 `local_bbox_x/y/z` 参数
- 增加或减少 `obstacle_search_radius`

**问题：编译错误**
- 确保已经编译了 `decomp_ros_msgs` 和 `decomp_ros_utils`
- 检查依赖包是否都已安装

## 作者

Fast-Exploration 项目团队

## 许可证

BSD

