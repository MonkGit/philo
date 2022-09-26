# philo

Here are the things you need to know if you want to succeed this assignment:
• One or more philosophers sit at a round table.
There is a large bowl of spaghetti in the middle of the table.
• The philosophers alternatively eat, think, or sleep.
While they are eating, they are not thinking nor sleeping; while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.
• There are also forks on the table. There are as many forks as philosophers.
• Because serving and eating spaghetti with only one fork is very inconvenient, a
philosopher takes their right and their left forks to eat, one in each hand.
• When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again. The simulation stops when a philosopher dies of starvation.
• Every philosopher needs to eat and should never starve.
• Philosophers don’t speak with each other.
• Philosophers don’t know if another philosopher is about to die.
• No need to say that philosophers should avoid dying!

>> The Solution for the Dining Philosophers Problem <<

In the Mandatory part we are dealing with Philosophers as threads and forks represented by mutexes. 
We need to avoid deadlocks.

In Bonus part Philosophers are processes and forks are semaphores.

We launch the program with additional arguments:
      * number_of_philosophers 
      * time_to_die
      * time_to_eat
      * time_to_sleep
      
and one optional argument:
      * number_of_times_each_philosopher_must_eat
      
Example: ./philo 4 410 200 200  
          ./philo 5 800 200 200 7
          
You can find philosophers vizualizer in web)
