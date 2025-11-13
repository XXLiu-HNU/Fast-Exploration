# 飞行走廊生成器使用指南

## 快速开始

### 1. 编译项目（已完成）

```bash
cd /home/xingxun/experiment/Fast-Exploration
catkin build
source devel/setup.bash
```

### 2. 启动你的仿真环境

首先需要启动你的主仿真系统，确保以下数据正在发布：
- 障碍物点云（发布到 `/map_ros/cloud` 话题）
- 地图数据

例如：
```bash
roslaunch exploration_manager exploration.launch
```

### 3. 启动飞行走廊生成器

在新的终端中运行：

```bash
source devel/setup.bash
roslaunch corridor_generator corridor_generator.launch
```

这将启动：
- corridor_generator_node 节点
- RViz 可视化工具（自动加载配置）

### 4. 在RViz中生成飞行走廊

1. **选择工具**：在RViz顶部工具栏，点击 "PublishPoint" 工具按钮
   - 图标通常是一个带有 + 号的点

2. **点击位置**：在3D视图中点击任意你想生成飞行走廊的位置

3. **查看结果**：系统会立即显示：
   - 红色球体：你点击的位置
   - 绿色箭头：飞行走廊边界的法向量
   - 蓝色线框：搜索边界框
   - 半透明多面体：实际的飞行走廊（如果启用了decomp插件）

### 5. 调整参数

如果生成的走廊不符合预期，可以修改launch文件中的参数：

```xml
<!-- 打开 launch/corridor_generator.launch -->

<!-- 增大走廊尺寸 -->
<param name="corridor_radius" value="2.0" type="double"/>

<!-- 增大搜索范围 -->
<param name="local_bbox_x" value="8.0" type="double"/>
<param name="local_bbox_y" value="8.0" type="double"/>
<param name="local_bbox_z" value="4.0" type="double"/>
```

修改后重新启动：
```bash
# Ctrl+C 停止当前节点
roslaunch corridor_generator corridor_generator.launch
```

## 常见使用场景

### 场景1：路径规划前的空间可行性检查

在规划路径前，可以先点击几个关键点，查看这些位置是否有足够的飞行空间。

### 场景2：验证狭窄通道

在狭窄通道（如门、窗）附近点击，查看无人机是否能安全通过。

### 场景3：动态调试

在仿真运行过程中，随时点击不同位置，实时查看不同区域的飞行走廊。

## RViz可视化说明

### 显示元素

1. **网格（Grid）**：世界坐标系网格
2. **Obstacle Cloud**：障碍物点云（白色点）
3. **Corridor Markers**：走廊标记
   - 中心点（红色球体）
   - 平面法向量（绿色箭头）
   - 边界框（蓝色线框）
4. **Flight Corridor**：多面体走廊（半透明彩色）

### 视角调整

- **旋转视角**：鼠标中键拖动
- **平移视角**：Shift + 鼠标中键拖动
- **缩放**：滚轮

### 切换显示

在RViz左侧的Displays面板中，可以勾选/取消勾选不同的显示项。

## 话题监控

### 查看话题列表

```bash
rostopic list | grep corridor
```

输出：
```
/corridor_generator/markers
/corridor_generator/polyhedrons
```

### 查看生成的走廊数据

```bash
rostopic echo /corridor_generator/polyhedrons
```

### 查看可视化标记

```bash
rostopic echo /corridor_generator/markers
```

## 故障排除

### 问题1：点击后没有反应

**检查点云数据：**
```bash
rostopic hz /map_ros/cloud
```

如果没有输出，说明点云数据没有发布。请确保：
- 仿真环境已启动
- 传感器（深度相机/激光雷达）正在工作
- 地图构建节点正在运行

**查看节点日志：**
```bash
rosnode list | grep corridor
rostopic info /clicked_point
```

### 问题2：走廊太小

**增大膨胀半径：**

编辑 `launch/corridor_generator.launch`：
```xml
<param name="corridor_radius" value="2.5" type="double"/>
```

### 问题3：走廊太大

**减小膨胀半径和边界框：**
```xml
<param name="corridor_radius" value="1.0" type="double"/>
<param name="local_bbox_x" value="3.0" type="double"/>
<param name="local_bbox_y" value="3.0" type="double"/>
<param name="local_bbox_z" value="2.0" type="double"/>
```

### 问题4：找不到障碍物

**检查话题名称：**

如果你的点云话题不是 `/map_ros/cloud`，需要修改代码或使用话题重映射：

```bash
roslaunch corridor_generator corridor_generator.launch \
  obstacle_cloud:=/your_cloud_topic
```

或者修改 `src/corridor_generator_node.cpp` 第26行：
```cpp
obstacle_cloud_sub_ = nh_.subscribe("/your_topic_name", 10, ...);
```

### 问题5：编译错误

```bash
# 清理并重新编译
cd /home/xingxun/experiment/Fast-Exploration
catkin clean corridor_generator
catkin build corridor_generator
```

## 高级使用

### 与其他节点集成

你可以订阅 `/corridor_generator/polyhedrons` 话题，在自己的规划节点中使用生成的飞行走廊：

```cpp
#include <decomp_ros_msgs/PolyhedronArray.h>

ros::Subscriber corridor_sub = nh.subscribe(
    "/corridor_generator/polyhedrons", 10, corridorCallback);

void corridorCallback(const decomp_ros_msgs::PolyhedronArrayConstPtr& msg) {
    // 使用走廊数据进行约束优化等
}
```

### 批量生成走廊

如果需要沿路径生成多个走廊，可以修改代码支持路径输入，或者编写脚本自动发布多个点。

## 参数参考

| 参数名 | 类型 | 默认值 | 说明 |
|--------|------|--------|------|
| corridor_radius | double | 1.5 | 飞行走廊膨胀半径（米） |
| local_bbox_x | double | 5.0 | X方向边界框半宽（米） |
| local_bbox_y | double | 5.0 | Y方向边界框半宽（米） |
| local_bbox_z | double | 3.0 | Z方向边界框半高（米） |
| obstacle_search_radius | double | 15.0 | 障碍物搜索半径（米） |

## 技术支持

如有问题，请查看：
1. 终端输出的错误信息
2. `/home/xingxun/experiment/Fast-Exploration/logs/corridor_generator/` 中的日志文件
3. RViz控制台输出

## 示例工作流程

```bash
# 终端1: 启动仿真
roslaunch exploration_manager exploration.launch

# 终端2: 启动走廊生成器
source devel/setup.bash
roslaunch corridor_generator corridor_generator.launch

# 然后在RViz中：
# 1. 选择 PublishPoint 工具
# 2. 在地图中点击多个位置
# 3. 观察生成的飞行走廊
# 4. 根据需要调整参数并重新测试
```

祝使用愉快！

