import sys
from xml.dom import minidom as DOM
import json

xhtmlFile = sys.argv[1]

def dfs_search(element, class_names):
    if element.nodeType == element.ELEMENT_NODE:
        class_attr = element.getAttribute('class')
        if all(class_name in class_attr.split() for class_name in class_names):
            return element
    for child in element.childNodes:
        result = dfs_search(child, class_names)
        if result is not None:
            return result
    return None

def find_element_by_class_names(doc, tag_name, class_names):
    elements = []
    for element in doc.getElementsByTagName(tag_name):
        if element.hasAttribute('class'):
            element_classes = element.getAttribute('class').split()
            if all(class_name in element_classes for class_name in class_names):
                elements.append(element)
    return elements


if xhtmlFile.startswith("downloaded_files/file1"):
    # parse for Michaels
    print("Michaels")
    sql_store_name = "Michaels"
    dom = DOM.parse(xhtmlFile)

    #### EXTRACT PRODUCT NAME ####
    elements = dom.getElementsByTagName("*")
    for elem in elements:
        if elem.hasAttribute('class') and 'smallScreenTop' in elem.getAttribute('class'):
            h1_tag = elem.getElementsByTagName('h1')[0]
            sql_product_name = h1_tag.firstChild.nodeValue
            print(sql_product_name)

    #### EXTRACT PRICE ####
    meta_tags = dom.getElementsByTagName("meta")
    # Search for the meta tag with specific property
    for tag in meta_tags:
        if tag.hasAttribute("property") and tag.getAttribute("property") == "og:price:amount":
            sql_price = tag.getAttribute("content")
            break
    print("Price:", sql_price)

    #### EXTRACT IMAGE URL ####
    img_tags = dom.getElementsByTagName("img")
    img_count = 0
    # Extract the src attribute value of the img tag
    for tag in img_tags:
        img_count +=1
        if tag.hasAttribute("src") and img_count == 6:
            image_url = tag.getAttribute("src")
            break
    print("Image URL:", image_url)



    #### EXTRACT REVIWS ####


else:
    # parse for Joann
    print("Joann")





'''
#connect to server
connection = mysql.connector.connect(
    host="localhost",
    user="mxxhxr",
    password="maahir2002",
    database="wsldatabase"
)
cursor = connection.cursor()

# create products table
cursor.execute(
    """
    CREATE TABLE IF NOT EXISTS products288 (
        product_name VARCHAR(255) PRIMARY KEY,
        description LONGTEXT,
        price FLOAT,
        image_url LONGTEXT,
        review_score INTEGER
        store_name VARCHAR(25)

    )
    """
)
#create orders table
cursor.execute(
    """
    CREATE TABLE IF NOT EXISTS orders288 (
        product_name VARCHAR(255) PRIMARY KEY,
        price FLOAT,
        store_name VARCHAR(255)
    )
    """
)

# also need to think about which store each item is from
    #if file starts with file1... or file2...
# loop through each file
# using minidom grab info and store in variables
# create sql insert function and insert into database
# repeat loop


connection.commit()
cursor.close()
connection.close()
'''