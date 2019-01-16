#! /bin/sh
# /etc/init.d/tello2 

### BEGIN INIT INFO
# Provides:          tello2
# Required-Start:    $remote_fs $syslog
# Required-Stop:     $remote_fs $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: Forward UDP packets to/from Tello
# Description:       See https://github.com/clydemcqueen/tello_ros
### END INIT INFO

case "$1" in
  start)
    echo "Starting tello2"
    /home/pi/udp_forward/udp_forward 0.0.0.0 12002 192.168.10.1 8889 &
    /home/pi/udp_forward/udp_forward 0.0.0.0 8890 192.168.86.105 13002 &
    /home/pi/udp_forward/udp_forward 0.0.0.0 11111 192.168.86.105 14002 &
    ;;
  stop)
    echo "Stopping tello2"
    killall udp_forward
    ;;
  *)
    echo "Usage: /etc/init.d/tello2 {start|stop}"
    exit 1
    ;;
esac

exit 0
