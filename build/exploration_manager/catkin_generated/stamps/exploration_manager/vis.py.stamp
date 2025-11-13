#!/usr/bin/env python

import rospy
from geometry_msgs.msg import PoseStamped, Point
from visualization_msgs.msg import Marker
from nav_msgs.msg import Path

class MultiUAVVisualizer:
    def __init__(self, num_uavs=3):
        rospy.init_node('multi_uav_visualizer', anonymous=True)

        self.num_uavs = num_uavs

        # Define the x and y offsets for each UAV 
        # ---------------------------------------------------
        # --------------Only use in Sim----------------------
        
        self.x_offsets = [3, 6, 9, 3, 6, 9, 3, 6, 9, 12]
        self.y_offsets = [0, 0, 0, -3, -3, -3, -6, -6, -6, -6]

        # --------------Only use in Sim----------------------
        # ---------------------------------------------------

        # UAV paths and publishers
        self.paths = {}
        self.path_pubs = {}
        self.icon_pub = rospy.Publisher('uav_icons', Marker, queue_size=10)
        self.line_pub = rospy.Publisher('uav_connections', Marker, queue_size=10)

        # Store UAV positions
        self.uav_positions = {}

        for i in range(0, num_uavs + 1):
            topic_name = f'/iris_{i}/mavros/vision_pose/pose'
            self.paths[i] = Path()
            self.paths[i].header.frame_id = "world"

            rospy.Subscriber(topic_name, PoseStamped, self.pose_callback, i)

            self.path_pubs[i] = rospy.Publisher(f'/uav{i+1}_path', Path, queue_size=10)

    def pose_callback(self, msg, uav_id):
        # Apply x and y offsets to the UAV's current pose

        # --------------Only use in Sim----------------------
        # ---------------------------------------------------

        # msg.pose.position.x += self.x_offsets[uav_id - 1]
        # msg.pose.position.y += self.y_offsets[uav_id - 1]

        # --------------Only use in Sim----------------------
        # ---------------------------------------------------
        # Store UAV position for line drawing
        self.uav_positions[uav_id] = msg.pose.position

        # Update and publish the path for this UAV
        self.paths[uav_id].header.stamp = rospy.Time.now()
        self.paths[uav_id].poses.append(msg)
        self.path_pubs[uav_id].publish(self.paths[uav_id])

        # Publish the UAV icon marker
        self.publish_uav_icon(uav_id, msg.pose)

        # Publish connection lines
        # self.publish_connections()

    def publish_uav_icon(self, uav_id, pose):
        icon_marker = Marker()
        icon_marker.header.frame_id = "world"
        icon_marker.header.stamp = rospy.Time.now()
        icon_marker.ns = "uav_icons"
        icon_marker.id = uav_id
        icon_marker.type = Marker.MESH_RESOURCE
        icon_marker.mesh_resource = "package://exploration_manager/scripts/meshes/hummingbird.mesh"  # 模型文件路径
        # icon_marker.mesh_use_embedded_materials = True

        icon_marker.action = Marker.ADD
        icon_marker.pose = pose

        # 设置模型的缩放
        icon_marker.scale.x = 1.0  # 缩放因子
        icon_marker.scale.y = 1.0
        icon_marker.scale.z = 1.0

        # 设置模型颜色
        icon_marker.color.r = 0.0
        icon_marker.color.g = 1.0
        icon_marker.color.b = 1.0
        icon_marker.color.a = 1.0  # 设置透明度，1.0为不透明

        # 发布模型标记
        self.icon_pub.publish(icon_marker)

    def publish_connections(self):
        # Create a Marker for lines
        line_marker = Marker()
        line_marker.header.frame_id = "world"
        line_marker.header.stamp = rospy.Time.now()
        line_marker.ns = "uav_connections"
        line_marker.id = 0
        line_marker.type = Marker.LINE_LIST
        line_marker.action = Marker.ADD
        line_marker.scale.x = 0.1  # Line width

        # Set line color
        line_marker.color.r = 1.0
        line_marker.color.g = 0.0
        line_marker.color.b = 0.0
        line_marker.color.a = 1.0

        # Define the connections between UAVs (example for a hexagon structure)
        connections = [
            (1, 2), (1, 3), (2, 3),(2, 4),(2, 5),(3, 5),(3, 6),
            (4, 5),(4, 7),(4, 8),(5, 6),(5, 8),(5, 9),(6, 9),(6, 10),
            (7, 8),(8, 9),(9, 10)
        ]

        # Add points for each connection
        for start, end in connections:
            if start in self.uav_positions and end in self.uav_positions:
                start_point = self.uav_positions[start]
                end_point = self.uav_positions[end]
                
                # Add start and end points to form a line
                line_marker.points.append(Point(x=start_point.x, y=start_point.y, z=start_point.z))
                line_marker.points.append(Point(x=end_point.x, y=end_point.y, z=end_point.z))

        # Publish the marker
        self.line_pub.publish(line_marker)

if __name__ == '__main__':
    try:
        visualizer = MultiUAVVisualizer(num_uavs=3)
        rospy.spin()
    except rospy.ROSInterruptException:
        pass
