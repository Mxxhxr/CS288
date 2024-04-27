
<html>
<head>
    <title>Buy Products</title>
    <link rel="stylesheet" href="styles.css?v=<?php echo time(); ?>">
    <style>
    <?php include "styles.css" ?>
    </style>
</head>
<body>


<?php
$cnx = new mysqli('localhost', 'mxxhxr', 'maahir2002', 'wsldatabase');
if ($cnx->connect_error)
    die('Connection failed: ' . $cnx->connect_error);

// Check if the 'id' parameter is set in the URL
if (isset($_GET['id'])) {
    $product_id = $_GET['id'];

    // Subtract 100 from the product ID if it belongs to Joanns (200-219)
    if ($product_id >= 200 && $product_id <= 219) {
        $product_id -= 100;
    }

    $query = "SELECT * FROM products288 WHERE product_id = $product_id";
    $cursor = $cnx->query($query);

    // Get the prices of both products
    $row1 = $cursor->fetch_assoc();
    $price1 = $row1['price'];

    $query = "SELECT * FROM products288 WHERE product_id = $product_id + 100";
    $cursor = $cnx->query($query);
    $row2 = $cursor->fetch_assoc();
    $price2 = $row2['price'];

    // Determine the lower price
    if ($price1 < $price2) {
        $lower_price = $price1;
        $higher_price = $price2;
    } else {
        $lower_price = $price2;
        $higher_price = $price1;
    }

    // Display both products with the lower price highlighted
    echo '<div class="product">';
    echo '<h3 class="product-info">Store Name</h3> <p class="info">' . $row1['store_name'] .'</p>';
    echo '<h3 class="product-info">Product Name</h3> <p class="info">' . $row1['product_name'] .'</p>';
    echo '<h3 class="product-info">Price</h3>';
    if ($row1['price'] == $lower_price) {
        echo '<p class="info highlight">$' . $row1['price'] * 1.20 .'</p>'; // Apply highlight class
    } else {
        echo '<p class="info">$' . $row1['price'] * 1.20  .'</p>';
    }
    echo '<h3 class="product-info">Review Score</h3> <p class="info">' . $row1['review_score'] .' Out Of 5</p>';
    echo '<img alt="Product Image" src="' . $row1['image_url'] . '" class="product-image"></img>';
    echo '<h3 class="product-info">Description</h3> <p class="info">' . $row1['description'] .'</p>';
    echo '<form method="post" action="add_to_cart.php">';
    echo '<input type="hidden" name="product_name" value="' . $row1['product_name'] . '">';
    echo '<input type="hidden" name="price" value="' . $row1['price'] * 1.20 . '">';
    echo '<input type="hidden" name="store_name" value="' . $row1['store_name'] . '">';
    echo '<input type="submit" name="add_to_cart" value="Add to Cart">';
    echo '</form>';
    echo '</div>';
    echo '<hr>';

    echo '<div class="product">';
    echo '<h3 class="product-info">Store Name</h3> <p class="info">' . $row2['store_name'] .'</p>';
    echo '<h3 class="product-info">Product Name</h3> <p class="info">' . $row2['product_name'] .'</p>';
    echo '<h3 class="product-info">Price</h3>';
    if ($row2['price'] == $lower_price) {
        echo '<p class="info highlight">$' . $row2['price'] * 1.20 .'</p>'; // Apply highlight class
    } else {
        echo '<p class="info">$' . $row2['price'] * 1.20  .'</p>';
    }
    echo '<h3 class="product-info">Review Score</h3> <p class="info">' . $row2['review_score'] .' Out Of 5</p>';
    echo '<img alt="Product Image" src="' . $row2['image_url'] . '" class="product-image"></img>';
    echo '<h3 class="product-info">Description</h3> <p class="info">' . $row2['description'] .'</p>';
    echo '<form method="post" action="add_to_cart.php">';
    echo '<input type="hidden" name="product_name" value="' . $row2['product_name'] . '">';
    echo '<input type="hidden" name="price" value="' . $row2['price'] * 1.20 . '">';
    echo '<input type="hidden" name="store_name" value="' . $row2['store_name'] . '">';
    echo '<input type="submit" name="add_to_cart" value="Add to Cart">';
    echo '</form>';
    echo '</div>';
    echo '<hr>';

} else {
    // Handle the case where 'id' parameter is not set
    echo "Product ID not specified";
}

$cnx->close();
?>
