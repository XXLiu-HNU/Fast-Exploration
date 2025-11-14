#!/usr/bin/env python3

import rospy
import numpy as np
import os
import sys

# 添加脚本所在目录到Python路径，以便导入同目录下的模块
script_dir = os.path.dirname(os.path.abspath(__file__))
if script_dir not in sys.path:
    sys.path.insert(0, script_dir)

from yolov11_detector import *


def main():
	rospy.init_node("yolov11_detector_node")
	yolo_detector()
	rospy.spin()

if __name__=="__main__":
	main()
	
