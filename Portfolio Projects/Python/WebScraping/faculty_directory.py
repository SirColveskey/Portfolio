"""
Name: Benjamin Cooper - bjc12b
Project: HW4 P1 - Faculty WebCrawler
Purpose: Analyzes the FSU CS department faculty page and compiles information on members
linked to from there. The information is compiled in a class faculty_member using requests
and regular expressions.
"""
import requests
import re

url = "http://www.cs.fsu.edu/department/faculty/"
pages = []
faculty = []

class faculty_member:
    def __init__(self,name,office,telephone,email):
        self.name = name
        self.office = office
        self.telephone = telephone
        self.email = email

def get_pages():
    main_page = requests.get(url)
    extensions = re.findall(r'<a href="http://www.cs.fsu.edu/department/faculty/([^/]+)/">', main_page.text)
    output = []
    for extension in extensions:
        if extension not in output:
            output.append(extension)
            pages.append("http://www.cs.fsu.edu/department/faculty/"+extension+"/")

def scrape_pages():
    for page in pages:
        working_page = requests.get(page)
        name = re.search(r'<title>([^|]+)| Computer Science</title>',working_page.text)
        office = re.search(r'<td><strong>Office:</strong></td>\n<td>([^<]+)</td>',working_page.text)
        telephone = re.search(r'<td><strong>Telephone:</strong></td>\n<td>([^<]+)</td>',working_page.text)
        email = re.search(r'<td valign="top"><strong>E-Mail:</strong></td>\n<td>([^<]+)</td>',working_page.text)
        if(name != None):
            name = name.group(1)
        else:
            name = "N/A"
        if(office != None):
            office = office.group(1)
        else:
            office = "N/A"
        if(telephone != None):
            telephone = telephone.group(1)
        else:
            telephone = "N/A"
        if(email != None):
            email = email.group(1)
        else:
            email = "N/A"
        staff = faculty_member(name,office,telephone,email)    
        faculty.append(staff)
        
def print_faculty():
    for staff in faculty:
        print "Name: " + staff.name
        print "Office: " + staff.office
        print "Telephone: " + staff.telephone
        print "E-Mail: " + staff.email
        print "************************************"
        
        
if __name__ == "__main__":
    get_pages()
    scrape_pages()
    print_faculty()
