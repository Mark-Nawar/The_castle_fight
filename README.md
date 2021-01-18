# The_castle_fight
A Datastructure simulation of the classical castle fight game where enemies are represented as Queues , Periority Queues and stacks. There is three types of enemies( Fighters,
freezers and healers)

Fighters :are the only ones that can decrement the health of the Castle and is them only that can make the castle lose the fight. If they all die that means that the Castle will eventually win the battle.

Frezzers :make the Castle freeze for one time step, there is a threshold that the freeers' attacks towards the castle will contribute towards. 
For example the the threshold is 10 , Freezer No1 attack will causse a freeze value of 2 , then we need 5 attacks from this freezer to freeze the castle.

Healer : They cannot attack the castle in any way but they have the ability to to heal the enemies that the castle attacked but with a constraint, the enemy must be within
a distance of MAX 2 m from the healer. 

Enemenis movement: All enemies start the game 60 M from the castle and get near the castle according to their speed, Fighters and freezers move only towards the Castle Healers 
can move back and forth towards and away from the Castle healing enemies along the way.


The Castle attack:The Castle can attack all enemies either by bullets or by ice with a ratio of attacking 80 : 20 respectivly.
the enemy that Got hit by a bullet will have his health decremented until it dies.
if the enemy is hit with ice it will be frosted in its location for some time steps where it cannot attack or make whatever action it is doing.


The Data Structures used to represent the enemies are:

Periority Queue for the Fighters
Periority Queue for the Frosted enemies
Queue for the freezers
Stack for the Healers 
Queue for the inactive enemies 
Queue for the killed enemies.



Every Enemy has a:
1)type 
2)Health
3)distance from the castle
4)power
5)reload period
6) frost count (Zero when not frosted)

The Castle has:
1)Max no of enemies to attack in a single time step.
2)The Castle Power 
3)The Castle Health 
4)The Freeze threshold 
5)the count towards the max freeze threshold

check the Project Pdf for all the details
THIS IS A CLASS PROJECT 
CAIRO UNIVERSITY , FACULTY OF COMPUTER ENGINEERING ,CLASS OF 2023
