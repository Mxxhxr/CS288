import sys
from xml.dom import minidom as DOM
import mysql.connector


xhtmlFile = sys.argv[1]

#all these functions are for description
def find_element_by_id(element, target_id):
    if element.nodeType == element.ELEMENT_NODE and element.getAttribute('id') == target_id:
        return element
    for child in element.childNodes:
        found_element = find_element_by_id(child, target_id)
        if found_element:
            return found_element
    return None

def get_text_content(element, start=False):
    text_content = ""
    for child in element.childNodes:
        if child.nodeType == child.TEXT_NODE:
            if start:
                text_content += child.data
        elif child.nodeType == child.ELEMENT_NODE:
            if start:
                text_content += get_text_content(child, start=True)
            elif child.tagName == "div" and "css-1bm3l7o" in child.getAttribute("class").split():
                start = True
                text_content += get_text_content(child, start=True)
    return text_content.strip()


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


def find_review_score(element):
    if element.nodeType == element.ELEMENT_NODE and element.nodeName == "p":
        class_attr = element.getAttribute('class')
        if 'chakra-text' in class_attr.split() and 'css-7q120u' in class_attr.split():
            return element.textContent.strip()
    for child in element.childNodes:
        result = find_review_score(child)
        if result is not None:
            return result
    return None


if xhtmlFile.startswith("downloaded_files/file1"):
    # parse for Michaels
    sql_store_name = "Michaels"
    dom = DOM.parse(xhtmlFile)

    #### EXTRACT PRODUCT NAME ####
    elements = dom.getElementsByTagName("*")
    for elem in elements:
        if elem.hasAttribute('class') and 'smallScreenTop' in elem.getAttribute('class'):
            h1_tag = elem.getElementsByTagName('h1')[0]
            sql_product_name = h1_tag.firstChild.nodeValue
            # print(sql_product_name, "\n")

    #### EXTRACT PRICE ####
    meta_tags = dom.getElementsByTagName("meta")
    # Search for the meta tag with specific property
    for tag in meta_tags:
        if tag.hasAttribute("property") and tag.getAttribute("property") == "og:price:amount":
            sql_price = tag.getAttribute("content")
            break
    # print("Price:", sql_price, "\n")

    #### EXTRACT IMAGE URL ####
    img_tags = dom.getElementsByTagName("img")
    img_count = 0
    # Extract the src attribute value of the img tag
    for tag in img_tags:
        img_count +=1
        if tag.hasAttribute("src") and img_count == 6:
            sql_image_url = tag.getAttribute("src")
            break
    # print("Image URL:", sql_image_url, "\n")



    #### EXTRACT REVIEWS ####
    # div_elements = dom.getElementsByTagName('p')
    # for div in div_elements:
    #     class_name = div.getAttribute('class')
    #     if class_name and ('chakra-text' in class_name.split() and 'css-1el49xh' in class_name.split()):
    #         # Extract text nodes from the div element
    #         text_content = ''.join(node.data.strip() for node in div.childNodes if node.nodeType == node.TEXT_NODE)
    #         print(text_content)
            # break
    sql_review_score = None

    #### EXTRACT DESCRIPTION ####
    text_desc = find_element_by_id(dom.documentElement, 'description')

    # Get the text content of the element
    if text_desc:
        sql_description = get_text_content(text_desc)
        # print(sql_description)
    else:
        print("Description element not found.")

else:
    # parse for Joann
    sql_store_name = "Joann"
    dom = DOM.parse(xhtmlFile)

    #### EXTRACT PRODUCT NAME ####
    sql_product_name = dom.getElementsByTagName('h1')[0].childNodes[0].nodeValue.strip()
    # print(sql_product_name)

    #### EXTRACT PRICE ####
    span_tags = dom.getElementsByTagName('span')
    for span in span_tags:
        if span.getAttribute('data-product-container') == 'sales-price':
            sql_price = span.childNodes[0].nodeValue.strip()
            # print(sql_price)
            break  # Stop after finding the first matching <span> tag

    #### EXTRACT IMAGE URL ####
    img_tags = dom.getElementsByTagName('img')
    for img in img_tags:
        sql_image_url = img.getAttribute('src')
        if sql_image_url.startswith('https://'):
            # print(sql_image_url)
            break

    #### EXTRACT REVIEWS ####
    span_elements = dom.getElementsByTagName('span')
    for i, span in enumerate(span_elements, start=1):
        if i == 32:
            # Get the text content of the span element
            sql_review_score = span.firstChild.nodeValue.strip()
            # Check if sql_review_score is a number
            try:
                float(sql_review_score)
            except ValueError:
                sql_review_score = None
            # print(sql_review_score)
            break

    #### EXTRACT DESCRIPTION ####
    div_elements = dom.getElementsByTagName('div')
    for div in div_elements:
        class_name = div.getAttribute('class')
        if class_name and ('cms-generic-copy' in class_name.split() and 'product__short-description' in class_name.split()):
            # Extract text nodes from the div element
            sql_description = ''.join(node.data.strip() for node in div.childNodes if node.nodeType == node.TEXT_NODE)
            print(sql_description)
            break  # Stop after finding the first matching div, remove this if you want to find all

    if not sql_description:
        sql_description = None
        print(sql_description)




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
        review_score INTEGER,
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


#update products table
cursor.execute(
    """
    INSERT INTO products288 (product_name, description, price, image_url, review_score, store_name)
    VALUES (%s, %s, %s, %s, %s, %s)
    """,
    (sql_product_name, sql_description, sql_price, sql_image_url, sql_review_score, sql_store_name)
)






connection.commit()
cursor.close()
connection.close()
