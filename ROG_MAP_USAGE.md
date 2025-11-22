# ROG Map 参数传递说明

## 当前情况分析

### 1. `exploration.launch` 的参数传递流程

```
exploration.launch
  ├─> 定义基础参数 (map_size_x, map_size_y, map_size_z, odom_topic 等)
  └─> 包含 algorithm.xml
      └─> 在 exploration_node 节点中设置参数
          ├─> sdf_map/* 参数 (用于传统 SDFMap)
          ├─> map_ros/* 参数
          ├─> fsm/* 参数
          ├─> exploration/* 参数
          └─> 其他算法参数
```

### 2. 是否使用了 ROG Map？

**是的，项目使用了 ROG Map！**

通过以下证据可以确认：

1. **代码依赖**：
   - `plan_manage` 包依赖 `rog_map` 包
   - `planner_manager.cpp` 包含 `#include <rog_map/plan_env_adapter.h>`

2. **适配器机制**：
   - `rog_map/plan_env_adapter.h` 提供了 `SDFMap` 适配器类
   - 适配器的 `initMap(ros::NodeHandle& nh)` 方法会创建 `rog_map::ROGMap`：
     ```cpp
     void initMap(ros::NodeHandle& nh) {
       rog_map_ = std::make_shared<rog_map::ROGMap>(nh);
     }
     ```

3. **参数命名空间**：
   - `rog_map::ROGMap` 构造函数读取 `rog_map/` 命名空间下的参数
   - 但 `algorithm.xml` 中设置的是 `sdf_map/` 参数

### 3. 参数配置问题

**当前存在参数命名空间不匹配的问题：**

- `algorithm.xml` 设置：`sdf_map/resolution`, `sdf_map/map_size_x` 等
- `rog_map::ROGMap` 需要：`rog_map/resolution`, `rog_map/map_size` 等

### 4. 解决方案

#### 方案 A：在 `algorithm.xml` 中添加 `rog_map` 参数

在 `algorithm.xml` 的 `<node>` 标签内添加：

```xml
<!-- ROG Map 参数 -->
<rosparam file="$(find rog_map)/config/rog_map_config.yaml" command="load" />

<!-- 或者直接设置参数 -->
<param name="rog_map/resolution" value="0.1" />
<param name="rog_map/map_size" value="[50.0, 50.0, 10.0]" />
<param name="rog_map/ros_callback/enable" value="true" />
<param name="rog_map/ros_callback/cloud_topic" value="/odin1/cloud_raw" />
<param name="rog_map/ros_callback/odom_topic" value="/odin1/odometry_highfreq" />
<param name="rog_map/visualization/enable" value="true" />
<param name="rog_map/visualization/range" value="[50.0, 50.0, 10.0]" />
```

#### 方案 B：修改 `exploration.launch` 加载 YAML 文件

在 `exploration.launch` 开头添加：

```xml
<launch>
  <!-- 加载 ROG Map 配置 -->
  <rosparam file="$(find rog_map)/config/rog_map_config.yaml" command="load" />
  
  <!-- 其他配置... -->
</launch>
```

### 5. 参数对应关系

| algorithm.xml 中的参数 | rog_map 中的对应参数 |
|----------------------|-------------------|
| `sdf_map/resolution` | `rog_map/resolution` |
| `sdf_map/map_size_x` | `rog_map/map_size[0]` |
| `sdf_map/map_size_y` | `rog_map/map_size[1]` |
| `sdf_map/map_size_z` | `rog_map/map_size[2]` |
| `sdf_map/p_hit` | `rog_map/raycasting/p_hit` |
| `sdf_map/p_miss` | `rog_map/raycasting/p_miss` |
| `sdf_map/p_min` | `rog_map/raycasting/p_min` |
| `sdf_map/p_max` | `rog_map/raycasting/p_max` |
| `sdf_map/p_occ` | `rog_map/raycasting/p_occ` |
| `sdf_map/min_ray_length` | `rog_map/raycasting/ray_range[0]` |
| `sdf_map/max_ray_length` | `rog_map/raycasting/ray_range[1]` |

### 6. 推荐配置方式

在 `exploration.launch` 中添加：

```xml
<launch>
  <!-- 加载 ROG Map 配置文件 -->
  <rosparam file="$(find rog_map)/config/rog_map_config.yaml" command="load" />
  
  <!-- 覆盖特定参数以匹配 exploration 设置 -->
  <param name="rog_map/map_size" value="[$(arg map_size_x), $(arg map_size_y), $(arg map_size_z)]" />
  <param name="rog_map/ros_callback/cloud_topic" value="$(arg cloud_topic)" />
  <param name="rog_map/ros_callback/odom_topic" value="$(arg odom_topic)" />
  
  <!-- 其他配置... -->
</launch>
```

这样既可以使用 YAML 文件的默认配置，又可以根据 launch 文件的参数动态调整。

