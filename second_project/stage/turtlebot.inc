define kinect ranger
(
  sensor
  (
    pose [ 0.0 0.0 0.0 0.0 ]
    size [0.1 0.1 0.1 ]
    range  [0 6.5]
    fov 270.0
    samples 640
  )
  # generic model properties
  color "black"
  size [ 0.6 0.4 0.03 ]
)

define turtlebot position
(
  pose [ 0.0 0.0 0.0 0.0 ]
  
  localization "odom"


  odom_error [0.0 0.0 0.0 0.0 ]

  size [ 0.2552 0.2552 0.40 ]
  origin [ 0.0 0.0 0.0 0.0 ]
  gui_nose 1
  drive "diff"
  color "grey"
  
  kinect()
)
