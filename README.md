# `udp_forward`

Forward UDP packets

## Example using Tello drones

Requirements:
* (2) Tello drones
* (2) Raspberry Pi 3 computers
* Host computer
* Ethernet switch with 2 free ports

Network the host computer and the 2 RPi3's together using Ethernet.

Set up [wifi on each RPi3](https://www.raspberrypi.org/documentation/configuration/wireless/wireless-cli.md)
so that each RPi3 connects to one of the Tello drones.

Edit `tello1.sh` and `tello2.sh` to match your network configuration.
Then install `udp_forward` and the startup scripts on the RPi3's.
Example for tello1.sh:

~~~
sudo cp tello1.sh /etc/init.d
sudo update-rc.d tello1.sh defaults
~~~ 

Now each time the RPi3's boot up they will forward the Tello UDP packets
to the host computer.