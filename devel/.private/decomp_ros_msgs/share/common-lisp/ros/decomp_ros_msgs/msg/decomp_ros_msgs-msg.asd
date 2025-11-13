
(cl:in-package :asdf)

(defsystem "decomp_ros_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "Ellipsoid" :depends-on ("_package_Ellipsoid"))
    (:file "_package_Ellipsoid" :depends-on ("_package"))
    (:file "EllipsoidArray" :depends-on ("_package_EllipsoidArray"))
    (:file "_package_EllipsoidArray" :depends-on ("_package"))
    (:file "Polyhedron" :depends-on ("_package_Polyhedron"))
    (:file "_package_Polyhedron" :depends-on ("_package"))
    (:file "PolyhedronArray" :depends-on ("_package_PolyhedronArray"))
    (:file "_package_PolyhedronArray" :depends-on ("_package"))
  ))