# iot-apps
This folder contains files for using OMA LWM2M on Contiki, specifically the Mulle platform from Eistec AB (http://www.eistec.se).

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


To add LWM2M functionallity to you project (I have tested with the rpl-border-router and er-rest-example) in Contiki:
1) Add the following include
#include "oma_lwm2m.h"
#include "resources/oma_lwm2m.h"

2) in the main process, add this code

  /* Initialize the REST engine. */
  rest_init_engine();
  
#if WITH_OMA_LWM2M == 1
  oma_lwm2m_init();
#endif

3) either copy the files from my repository to your Contiki tree, or use symblic links in Linux to add alla my files to your resorces/ folder. 
This will be improved when my code is pushed to the standard Contiki reposity in apps/oma-lwm2m or similar.

4) enable LWM2M to your build bu add ing the following code snippet to your project_conf.h

// enable OMA LwM2M framework
#define WITH_OMA_LWM2M	1

# Not currently working du to problem when the /bs server performs a DELETE to the "/" resource
To work with the bootstrap functionality (note that the bootstrap and main leshan servers cannot run at the same time due to port collisions):
1) Build the leshan bootstrap server
 $ cd leshan-bs-server
 $ mvn assembly:assembly -DdescriptorId=jar-with-dependencies
 $ java -jar target/leshan-bs-server-0.1.11-SNAPSHOT-jar-with-dependencies.jar

2) From another terminal, add a device, and change Mulle-202 to meet the name of your device and
  create a config for your bootstrap server and devices
 $ curl --data-binary @config.json http://localhost:8080/api/bootstrap/Mulle-202


