"""
Name: Benjamin Cooper - bjc12b
Project: Python Midterm
Date: 7/5/2016

--- Fatal Error ---
The player will be placed in a 5x5 grid at the left edge center position.
There will be four enemy encounter locations, one Backpack, and one Rat Trap
The backpack is the objective, the Rat Trap is an instant loss.
There are five commands that the user can perform
       =====Commands=====
       help - Prints currently available commands
       quit - Prints a message and ends the game
       go [N,S,E,W] - Moves the player one space in the direction
       health - Prints the players current HP
       attack - Attacks the current opponent
There is one type of enemy:
   the Evil Robot with 15 HP, 9 Str, 7 Def
The player can choose one of two classes:
   CodeWarrior with 30 HP, 10 Str, 8 Def
   1337H4x0r with 30 HP, 8 Str, 10 Def
The implementation will be as follows:
A Character class which derives Evil Robot and Player
A Player class which derives CodeWarrior and H4x0r
An Evil Robot Class
A Code Warrior Class
A H4x0r Class
The methods help(), health(), go(), attack(), and quit() are defined in player
***
This version of the program is designed to be run on ubuntu machines using a telnet connection
Command: telnet localhost 9000
***
"""
from __future__ import print_function
from random import * #for use in placing the board
from socket import * #for use in networking
import threading #to allow multiple instances

class board:
    def __init__(self,c):
        self.board = [["","","","",""],["","","","",""],["","","","",""],["","","","",""],["","","","",""]]
        self.c = c
        for i in range (0,4):#sets up the four monsters
            randx = randint(0,4)
            randy = randint(0,4)
            while self.board[randx][randy] != "" and not(randx == 0 and randy == 2):
                randx = randint(0,4)
                randy = randint(0,4)
            self.board[randx][randy] = EvilRobot(c)
        randx = randint(0,4)
        randy = randint(0,4)#sets up the backpack and rattrap
        while self.board[randx][randy] != "" and not(randx == 0 and randy == 2):
            randx = randint(0,4)
            randy = randint(0,4)
        self.board[randx][randy] = "B"
        randx = randint(0,4)
        randy = randint(0,4)
        while self.board[randx][randy] != "" and not(randx == 0 and randy == 2):
            randx = randint(0,4)
            randy = randint(0,4)
        self.board[randx][randy] = "R"

    def getEvent(self,c,pos):#calls to return what is on this position of the board
        return self.board[pos[0]][pos[1]]

    def killEvent(self,c,pos):#call to kill whatever is on the board at this position (used for enemies)
        self.board[pos[0]][pos[1]] = ""

class character:#parent class - not designed for use
    def __init__(self,c):
        self.c = c
        self.hp = 0
        self.strength = 0
        self.defense = 0



class Player(character):#parent class for all player classes - defines actions players can take
    def __init__(self,c):
        printOut(c,"Enter a name for your character: ")
        self.position = [0,3]
        self.name = printIn(c)
        self.combat = False
        self.enemy = "none"
        self.board = board(c);
        self.playing = True
        
    def help(self,c):#run to print out appropriate command dialogue
        printOut(c,"Available Commands:\n")
        if self.combat:
            printOut(c,"health\nattack\nquit\n")
        else:
            printOut(c,"health\ngo [N,S,W,E]\nquit\n")
            
    def health(self,c):
        printOut(c,str(self.hp)+"\n")

    def go(self,c,dir):#contains movement processing and triggers arrivals
        if self.combat:
            printOut(c,"You are in combat, you cannot leave.\n")
            return
        if dir == "N":
            if(self.position[1] + 1 > 4):
                printOut(c,"{} runs into a wall.\n",self.name)
                return
            self.position[1] += 1
        elif dir == "S":
            if(self.position[1] - 1 < 0):
                printOut(c,"{} runs into a wall.\n",self.name)
                return
            self.position[1] -= 1
        elif dir == "W":
            if(self.position[0] - 1 < 0):
                printOut(c,"{} runs into a wall.\n",self.name)
                return
            self.position[0] -= 1
        elif dir == "E":
            if(self.position[0] + 1 > 4):
                printOut(c,"{} runs into a wall.\n",self.name)
                return
            self.position[0] += 1
        interaction = self.board.getEvent(c,self.position)
        if interaction == "":
            printOut(c,"Nothing is found...\n")
        elif interaction == "B":
            printOut(c,"The backpack has been found! Victory!\n")
            self.ex(c)
        elif interaction == "R":
            printOut(c,"You have stepped on a rat trap! You're dead. Better luck next time!\n")
            self.ex(c)
        else:
            printOut(c,"You have stumbled across an enemy "+interaction.name+"\nPrepare to fight!\n")
            self.combat = True
            self.enemy = interaction
            
    def attack(self,c):
        if self.combat:
            damage(c,self,self.enemy)
            if(self.enemy.hp <= 0):
                printOut(c,"{} has been slain!\n",self.enemy.name)
                self.combat = False
                self.enemy = "none"
                self.board.killEvent(c,self.position)
                return
            damage(c,self.enemy,self)
            if(self.hp <= 0):
                printOut(c,"{} has been slain! You're dead. Better luck next time!",self.name)
                self.ex(c)
                
        else:
            printOut(c,"There is nothing to attack.\n")
            return

    def quit(self,c):
        printOut(c,"Tired of RNG failing them, {} opts to retire and accept their demise.\n",self.name)
        self.ex(c)

    def ex(self,c):
        c.close()
        self.playing = False#playing is used to kill the primary game loop
#improvements could be made here by implementing the parent initializers (a little bit of repeated code occurs)
class CodeWarrior(Player):
    def __init__(self,c):
        self.c=c
        self.playing=True
        printOut(c,"Enter a name for your character: ")
        self.position = [0,2]
        self.name = printIn(c)
        self.combat = False
        self.enemy = "none"
        self.board = board(c);
        self.hp = 30#what you would edit to balance classes
        self.strength = 10
        self.defense = 8

class H4x0r(Player):
    def __init__(self,c):
        self.c = c
        self.playing=True
        printOut(c,"Enter a name for your character: ")
        self.position = [0,2]
        self.name = printIn(c)
        self.combat = False
        self.enemy = "none"
        self.board = board(c);
        self.hp = 30#what you would edit to balance classes
        self.strength = 8
        self.defense = 10

class EvilRobot(character):
    def __init__(self,c):
        self.c = c
        self.name = "Evil Robot"
        self.hp = 15#what you would edit to change "difficulty" (given this is a very flat game with no choices, difficulty is simply percentage of victory)
        self.strength = 9
        self.defense = 7

def damage(c,self,enemy):
    """handles damage calculation and modification"""
    damage = randint(0, 6) + self.strength-enemy.defense #what you would edit to change range of damages
    if damage <= 0:
        printOut(c,"{} evades {}'s attack.\n",enemy.name,self.name)
    else:
        enemy.hp = enemy.hp - damage
        printOut(c,"{} attacks {} for {} points of damage!\n",self.name, enemy.name, str(damage))

def printOpener(c):
    printOut(c,"Hello! Welcome to Fatal Error! Enjoy your stay... (Enter help for commands)\n")

def printOut(c, s, arg1="", arg2="", arg3=""):
    """printOut takes in 3 possible arguments for a formatted string
    (could implement using *args but couldn't figure it out yet). It then c.sends the formatted string.
    thought: could just preformat the strings, should be able to accept a formatted string."""
    
    if(arg1 != ""):
        c.send(s.format(arg1,arg2,arg3))
    else:
        c.send(s)

def printIn(c):
    """printIn gets input from the socket, and strips a newline. Limited to 128 bytes."""
    return c.recv(128).rstrip()
    
def LaunchGame(c):
    """LaunchGame is the primary driver function."""
    printOpener(c)
    cl = ""
    while cl != "c" and cl != "h":
        printOut(c,"Would you like to play a CodeWarrior (c) or 1337H4x0r (h)? ")
        cl = printIn(c)
        if cl == "c":
            player = CodeWarrior(c)
        elif cl == "h":
            player = H4x0r(c)
        else:
            printOut(c,"Please reply with 'c' or 'h'")
    printOut(c,"{} enters the lab in search of his backpack...\n",player.name)
    while player.playing:
        command = printIn(c)
        if command == "help":
            player.help(c)
        elif command == "quit":
            player.quit(c)
        elif command == "health":
            player.health(c)
        elif command == "attack":
            player.attack(c)
        elif command == "go N":
            player.go(c,"N")
        elif command == "go S":
            player.go(c,"S")
        elif command == "go W":
            player.go(c,"W")
        elif command == "go E":
            player.go(c,"E")
        else:
            printOut(c,"Invalid command... reinput\n")
        #print(player.board.board)

if __name__ == "__main__":
    """basic threading with sockets used. Sim. blackjack example from class."""
    s = socket(AF_INET,  SOCK_STREAM)
    s.bind(("", 9000))
    s.listen(5)
    while True:
        c, a = s.accept()
        t = threading.Thread(target=LaunchGame,  args=(c,))
        t.start()

