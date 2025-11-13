
(cl:in-package :asdf)

(defsystem "bspline-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
)
  :components ((:file "_package")
    (:file "Bspline" :depends-on ("_package_Bspline"))
    (:file "_package_Bspline" :depends-on ("_package"))
  ))