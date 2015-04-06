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
3) Run the Mulle device  with the Resource Directory client and the correct IP address [fdfd::ff] when using the Mulle
4) When the Mulle device has registered at the RD server, use a web browser to see all resources of the Mulle at: http://localhost:8080/#/clients


To work with the bootstrap funtionality (note that the bootstrap and main leshan servers canot run at the same time due to port collisions):
1) Build the leshan bootstrap server
 $ cd leshan-bs-server
 $ mvn assembly:assembly -DdescriptorId=jar-with-dependencies
 $ java -jar target/leshan-bs-server-0.1.11-SNAPSHOT-jar-with-dependencies.jar

2) From another terminal, add a device, and change Mulle-202 to meet the name of your device and
  create a config for your bootstrap server and devices
 $ curl --data-binary @config.json http://localhost:8080/api/bootstrap/Mulle-202


