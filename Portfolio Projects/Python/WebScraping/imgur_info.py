"""
Name: Benjamin Cooper - bjc12b
Project: HW4 P2 - imgur Comment Analyzer
Purpose: Find the five most well scored comments for a user supplied username
on imgur. It uses a custom comment class which is populated using requests and jsons.
Relevant informtion is then parsed out and sorted using the __cmp__ function.
"""
import requests
import json

class comment:
    def __init__(self,name,points,title,date):
        self.name = name
        self.points = points
        self.title = title
        self.date = date
    def __cmp__(self,other):
        if self.points < other.points:
            return -1
        elif self.points > other.points:
            return 1
        elif self.name < other.name:
            return -1
        elif self.name > other.name:
            return 1
        else:
            return 0
        
pages = []
comments = []

username = raw_input('Enter username: ')
counter = 0
page = " "
while page != "":
    page = requests.get("http://imgur.com/user/"+username+"/index/newest/page/"+str(counter)+"/hit.json?scrolling").text
    counter += 1
    if page != "":
        pages.append(page)
counter = 0
for x in pages:
    dict = json.loads(x)['data']['captions']['data']
    for y in dict:
        name = y['hash']
        points = y['points']
        title = y['title']
        date = y['datetime']
        comments.append(comment(name,points,title,date))
comments.sort()
comments.reverse()
for x in comments:
    counter += 1
    print str(counter) + ". " + x.name
    print "Points: " + str(x.points)
    print "Title: " + x.title
    print "Date: " + x.date
    print ""
    if counter == 5:
        break
