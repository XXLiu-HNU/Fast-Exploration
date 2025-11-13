# Fast-Exploration

基于 FUEL 的快速探索项目，通过 Gazebo 仿真更接近真实实验环境。

## 主要更新

1. 添加了控制器的一键起飞功能
2. 优化了可视化界面
3. **新增飞行走廊生成器** - 支持交互式生成安全飞行走廊

## 飞行走廊生成器使用方法

### 功能说明

飞行走廊生成器允许用户在 RViz 中点击选择位置，自动生成该位置的安全飞行走廊并可视化。使用 DecompROS 库的 SeedDecomp 算法，根据障碍物信息生成凸多面体走廊。

### 快速使用

#### 1. 启动节点

```bash
roslaunch corridor_generator corridor_generator.launch
```

#### 2. 在 RViz 中操作

1. 在 RViz 工具栏中选择 "PublishPoint" 工具
2. 在 3D 视图中点击任意位置
3. 系统将自动生成并显示该位置的飞行走廊

### 参数配置

可在 launch 文件中调整以下参数：

```xml
<!-- 走廊半径 -->
<param name="corridor_radius" value="1.5"/>

<!-- 局部边界框大小 -->
<param name="local_bbox_x" value="5.0"/>
<param name="local_bbox_y" value="5.0"/>
<param name="local_bbox_z" value="3.0"/>

<!-- 障碍物搜索半径 -->
<param name="obstacle_search_radius" value="15.0"/>
```

### 可视化

生成的飞行走廊包含：
- **红色球体**：选中的种子点
- **绿色箭头**：多面体的平面法向量
- **蓝色线框**：局部边界框
- **半透明多面体**：实际的飞行走廊

### 详细文档

更多详细信息请参考：[走廊生成器文档](src/Utils/corridor_generator/README.md)

## 参考项目

1. [XTDrone](https://github.com/robin-shaun/XTDrone) - 仿真平台
2. [Fast-Drone-250](https://github.com/ZJU-FAST-Lab/Fast-Drone-250) - 控制器模块
3. [FUEL](https://github.com/HKUST-Aerial-Robotics/FUEL) - 规划模块

## 许可证

BSD
