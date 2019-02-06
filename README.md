MQTT Water Sensor

Inspired by the work by 
- Rob from The Hookup - https://www.youtube.com/watch?v=2kLZ7DlP9KU and 
- Peter Jennings - http://benlo.com/esp8266/esp8266WaterAlarm.html

I was looking around for a while for a sensor that would be
- battery operated
- wireless
- small
- with battery life from one year 
- would use MQTT

and found nothing.

I had to come up with something on my own.

Out of the box solutions like Xiaomi sensors were not acceptable since they use an additional hub that I did not know would work on the local level or not (my aim is to keep all smart home traffic within the LAN). Other solutions would either be non-smart with great battery life of be smart with a very short battery life (a couple of months). 

Then I ran into Rob's (The Hookup) window sensor - https://www.youtube.com/watch?v=BoYVr2UwWWg  I immediately tried his setup but instead of the reed switch I was hoping to use water to complete the cirquit. No luck. Water is not a good conductor in this case. So I had to look elsewhere. But I took his code for ESP-01 and modified it slightly ("on/off" instead of "open/close" although this modificatin might not be required). 

I found a few circuits that could work for my purpose but I do not have enouth electronics knowledge to convert those to work from a 3 volt battery. Circuit one below could work, but I have not tried it yet.

<img src="https://cdn.instructables.com/FGO/5G9D/FH9ZFLVQ/FGO5G9DFH9ZFLVQ.LARGE.jpg?auto=webp&width=400"/><img src="https://cdn.instructables.com/FVT/Z80Z/FHOHJJMD/FVTZ80ZFHOHJJMD.LARGE.jpg?auto=webp&width=300"/>

Source - https://www.instructables.com/id/Simple-Water-Sensor/

Then I ran into Peter Jennings' work on his water sensor - http://benlo.com/esp8266/esp8266WaterAlarm.html. The switch he used was an answer - https://www.pololu.com/product/2808. 

<img src="https://a.pololu-files.com/picture/0J6789.600x480.jpg?a4cf523daa68a0fc751c6ff85fb0ffc6">

I contacted Peter and he confirmed that in a standby mode the switch was not consuming much at all (official spec says 0.01 micro Amperes).

Here is how you hook up ESP-01 to FTDI:
<img src="http://1.bp.blogspot.com/-2zMMrsmzNVk/VzkpezD6j2I/AAAAAAAAFNE/VU5DisFVRMMaz1S0S7R-j8CTe0j_ot8sACK4B/s1600/Circuito-ESP8266-ESP-01-FTDI-FT232.png"/>

Then flash it using the ESP-01_Water_Sensor.ino file

Here is the final connection diagram:
<img src="http://benlo.com/esp8266/Water_Sensor_ESP8266_Circuit.jpg"/>

ESP-01 code and Home Assistant samples are in the files of this repository.

So, the end result works like this: once water is closing the sensor probes (basically two wires sticking out), the switch turns on ESP-01 and ESP-01 sends an MQTT message with 'on' to a topic and then goes into a deep sleep. All other actions are triggered in Home Assistant using automations and scripts.

In my setup, Home Assistant will then send a command to the dry contact switch (<a href="https://www.chatteris.biz/blog/sonoff-basic-voltage-free-relay-changeover-modification/" target="_blank">modified Sonoff</a>) to close the Electric Manipulator Shut Off Valve gizmo that I purchased on Amazon. I retrofitted a polarity switch and power input jack. 

<img src="http://relit.ca/wp-content/uploads/2019/02/Electric-Automatic-Manipulator-Shut-Off-Valve-for-Alarm-Gas-Water-Pipeline-Security-Device-Assortment-12V-1.jpg"/>

Here is the video with the setup.
[![Watch the video](https://img.youtube.com/vi/RAxCV2L04LM/sddefault.jpg)](https://www.youtube.com/watch?v=RAxCV2L04LM)
