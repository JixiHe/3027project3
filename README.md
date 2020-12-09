# project-3---signaling-with-multi-process-programs-JixiHe

Since I had so much trouble to commit my project on this repo, this probably because I am using Macbook with CLion instead of Windows, I had created a new repo...

If you want to see all the commits, here is the link:

https://github.com/JixiHe/3027project3

The program generate 8 process

As you can see that sig_1 and sig_2 are generated 

![p1](https://user-images.githubusercontent.com/60365593/100679984-a2f6bc00-333e-11eb-9acf-d4e081664c4c.png)


In the below, there is some output, where SIGUSR1 and SIGUSR2 are the two signals for communication. They are generated processes are executed in a loop where will repetly and randomly select from SIGUSR1 or SIGUSR2 to send processes.

Random time delay ranging between .01 second and .1 second and it shows on the current time
![p1](https://user-images.githubusercontent.com/60365593/100679910-80fd3980-333e-11eb-84aa-9e7ee4ae1d6f.png)

30 seconds result:
![p2](https://user-images.githubusercontent.com/60365593/100681103-01bd3500-3341-11eb-9fbe-1f888a8ed3d8.png)



100,000 signals result:
![p1](https://user-images.githubusercontent.com/60365593/100681143-1c8fa980-3341-11eb-8595-10aee6f73414.png)
