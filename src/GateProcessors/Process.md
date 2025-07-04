
gates will be stored on a constant array


0 - buffer
1 - not gate
2 - and gate
3 - or gate
4 - not gate
5 - nand gate
6 - xor gate


custom component will be stored on a vector containing the


256 and up - custom component




- the process will start on initiations, defining objs, and initiating objects
- then pre-evaluate the circuit objs to make sure loops, and circuit that has long internal delay
will finish before execution along with processing the routs
- followed by starting the process loop
- start processing each objs (gates, IC, devices, etc)
- if the user do some editing, re calculate the routes
