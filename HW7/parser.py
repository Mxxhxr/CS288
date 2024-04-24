import mysql.connector

#connect to server
connection = mysql.connector.connect(
    host="localhost",
    user="mxxhxr",
    password="maahir2002",
    database="wsldatabase"
)
cursor = connection.cursor()

#create table if not already made
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
# also need to think about which store each item is from
# loop through each file
# using minidom grab info and store in variables
# create sql insert function and insert into database
# repeat loop

# update table with store name




connection.commit()
cursor.close()
connection.close()