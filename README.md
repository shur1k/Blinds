# Blinds
A library for controliing the window blinds. It's supposed to control the blinds with a pair of relays with tree contacts (NC, Common, NO), connected to the digital PINs of the arduino compatible MCU. The blinds should have the electric motor with three wire connection (a common (negative) wire, a wire to spin forward and a wire to spin backward). 
For a safety reason, one of the relays should be used to switch on and off the Power and the other relay will switch between the direction wires of the motor. It means that to spin forward just Power relay will be swithed on, to spin backwars the both relays will be switched on. 
The connection shoiuld look like the following:
*             Forward Backward                
  Power wire   wire    wire
  
     |           |     |
     |   --------|--   |
     |  |        |  |  |
     
 ---------      ---------
| o  o  o |    | o  o  o |
 ---------      ---------

NC  C  NO      NC  C  NO
 
 The common (zero) wire shoulb be connected to the motor permanently. 
 The exmaple inside contains a sketch, wich shows, how to initialize the Blinds: you should pass the two digital PINs, where the relays are connedted to, the maximum spinning time (the operation time to fully open the blinds from the closed state)
