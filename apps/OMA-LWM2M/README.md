# iot-apps
This folder contains files for using OMA LWM2M on Contiki, spcifically the Mulle platform from Eistec AB.

Contact: jens.eliasson@ltu.se or jens.eliasson@gmail.com

Testing:
1) Download leshan server at https://github.com/eclipse/leshan
2) Build the server using the provided instructions, e.g.
 $ git clone https://github.com/eclipse/leshan.git
 $ cd leshan
 $ mvn install
 $ cd leshan-standalone
 $ mvn assembly:assembly -DdescriptorId=jar-with-dependencies

3) Create a config for your server and devices
 $ <to be added>
