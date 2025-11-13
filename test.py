#!/usr/bin/env python3
import rospy
from geometry_msgs.msg import Point
from visualization_msgs.msg import Marker, MarkerArray

if __name__ == "__main__":
    rospy.init_node("test_corridor_markers")
    pub = rospy.Publisher("/sdf_map/corridor_markers", MarkerArray, queue_size=1, latch=True)
    rospy.sleep(1.0)

    markers = MarkerArray()

    # 填充面 (TRIANGLE_LIST)
    fill_marker = Marker()
    fill_marker.header.frame_id = "world"
    fill_marker.header.stamp = rospy.Time.now()
    fill_marker.ns = "corridor_polyhedron"
    fill_marker.id = 0
    fill_marker.type = Marker.TRIANGLE_LIST
    fill_marker.action = Marker.ADD
    fill_marker.pose.orientation.w = 1.0
    fill_marker.scale.x = fill_marker.scale.y = fill_marker.scale.z = 1.0
    fill_marker.color.r = 0.1
    fill_marker.color.g = 0.6
    fill_marker.color.b = 0.9
    fill_marker.color.a = 0.3

    triangles = [
        (0, 0, 0), (1, 0, 0), (0, 1, 0),
        (1, 0, 0), (1, 1, 0), (0, 1, 0),
        (0, 0, 0), (0, 1, 0), (0, 0, 1),
        (0, 1, 0), (1, 1, 0), (0, 0, 1),
        (1, 1, 0), (1, 0, 0), (0, 0, 1),
        (1, 0, 0), (0, 0, 0), (0, 0, 1),
    ]
    for x, y, z in triangles:
        pt = Point(x=x, y=y, z=z)
        fill_marker.points.append(pt)

    # 边框 (LINE_LIST)
    edge_marker = Marker()
    edge_marker.header.frame_id = "world"
    edge_marker.header.stamp = fill_marker.header.stamp
    edge_marker.ns = "corridor_polyhedron"
    edge_marker.id = 1
    edge_marker.type = Marker.LINE_LIST
    edge_marker.action = Marker.ADD
    edge_marker.pose.orientation.w = 1.0
    edge_marker.scale.x = 0.05
    edge_marker.color.r = 0.1
    edge_marker.color.g = 0.8
    edge_marker.color.b = 0.3
    edge_marker.color.a = 1.0

    edges = [
        (0, 0, 0), (1, 0, 0),
        (1, 0, 0), (1, 1, 0),
        (1, 1, 0), (0, 1, 0),
        (0, 1, 0), (0, 0, 0),
        (0, 0, 0), (0, 0, 1),
        (1, 0, 0), (0, 0, 1),
        (1, 1, 0), (0, 0, 1),
        (0, 1, 0), (0, 0, 1),
    ]
    for x, y, z in edges:
        pt = Point(x=x, y=y, z=z)
        edge_marker.points.append(pt)

    markers.markers.append(fill_marker)
    markers.markers.append(edge_marker)

    pub.publish(markers)
    rospy.loginfo("测试 MarkerArray 已发布，话题 /sdf_map/corridor_markers")
    rospy.spin()