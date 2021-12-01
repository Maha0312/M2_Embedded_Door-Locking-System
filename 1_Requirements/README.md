# INTRODUCTION

Password based Door locking system is a safe and secure access control to use. 

## Aim

To design a Password based door locking system, using Matrix keypad to enter the password.
This project is extended to operate on IR Remote RC-604.

## Features
1. You can enter password through Keypad or IR Remote
2. Low Cost
3. Simple to design
4.Password protected access
5.Eliminates the need to carry a key or any extra remote, as the users phone is used
6.The entire process requires virtually no time



## Research 
Using physical keys to lock or unlock the door is the most natural way and everyone is acquainted with it. The physical key is a well-tested and well-known technology, but it also has its flaws. There can only be one unique key for a lock. For different locks you have different keys. Furthermore, carrying a large number of keys is a burden and increases the chance of keys getting stolen, misplaced or lost.Our goal is to design a solution for secure access control that can replace physical keys for accessing door. 


## Benefits

1.This project provides security
2.Power consumption is less
3.Used commonly available components
4.Project is simple and easy







## High level requirements

ATMEGA 328
LCD Display
Transistor
Voltage Regulator



## Low level requirements

Resistors
Relays
Switches
Keypad Matrix
Program coding


## System Control Flow
### First Use Mode
The user will be prompted to enter a password and confirm it using the keypad.<br/>
If the passwords match, the password will be transmitted to the controller ECU to be saved in the external EEPROM and a friendly message will be displayed on the LCD to confirm that the password is successfully saved. Otherwise, a message will be displayed to inform the user that the passwords mismatch and the whole process will be repeated again.

### Normal Mode 
The user will be prompted to enter his password using the keypad.<br/>
If the password is correct, the supported operations menu will be displayed to the user on the LCD to choose the action he wants to perform, he could either request to open the door or change the password.<br/>
However, if the password is incorrect the user can enter the password maximum of 3 times then the system will freeze and trigger the alarm.
##### Request to Open Door
If the controller ECU (actuator) receives a signal to open the door, it will rotate the motor in clockwise direction opening the door, wait for few minutes then close the door again.
##### Request to Change Password
If the user chooses to change the password, he will be prompted to enter a password and confirm it using the keypad. then it will be sent to the controller to store it instead of the old one.


# 4W's and 1H's



## Who
It can be used by anyone who wishes to keep more safe and secure locking system



## What
Password based door locking system for security purposes



## When
Whenever the owner wants more safety setup for their home door. 


## Where
Can be used in home, shops, offices etc

## How
It is locking system that is used to open or close the door using password


# SWOT Analysis
[swotanalysisM2](https://user-images.githubusercontent.com/94235122/144185447-5c9afbb5-4a18-4997-a39f-e50e73bdf724.png)

