#! /bin/sh
# /etc/init.d/tello1

### BEGIN INIT INFO
# Provides:          tello1
# Required-Start:    $remote_fs $syslog
# Required-Stop:     $remote_fs $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: Forward UDP packets to/from Tello
# Description:       See https://github.com/clydemcqueen/tello_ros
### END INIT INFO

case "$1" in
  start)
    echo "Starting tello1"
    /home/pi/udp_forward/udp_forward 0.0.0.0 12001 192.168.10.1 8889 &
    /home/pi/udp_forward/udp_forward 0.0.0.0 8890 192.168.86.105 13001 &
    /home/pi/udp_forward/udp_forward 0.0.0.0 11111 192.168.86.105 14001 &
    ;;
  stop)
    echo "Stopping tello1"
    killall udp_forward
    ;;
  *)
    echo "Usage: /etc/init.d/tello1 {start|stop}"
    exit 1
    ;;
esac

exit 0
