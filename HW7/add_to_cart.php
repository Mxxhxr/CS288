

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

if (isset($_POST['add_to_cart'])) {
    $product_name = $_POST['product_name'];
    $price = $_POST['price'];
    $store_name = $_POST['store_name'];

    $query = "INSERT INTO orders288 (product_name, price, store_name) VALUES ('$product_name', $price, '$store_name')";
    if ($cnx->query($query) === TRUE) {
        echo "<h1 class='orders-header'>Product added to cart successfully.</h1>";
        echo "<h2 class='orders-header'>Thank you for purchasing on my site.</h2";
        echo "<br>";
        echo "<br>";
        echo "<br>";
        echo "<br>";
    } else {
        echo "Error: " . $query . "<br>" . $cnx->error;
    }
}

$cnx->close();
?>

<!DOCTYPE html>
<html>
<head>
    <title>Add to Cart</title>
    <link rel="stylesheet" href="styles.css?v=<?php echo time(); ?>">
    <style>
    <?php include "styles.css" ?>
    </style>
</head>
<body>

<button onclick="window.location.href='index.php'">Go back to Home</button>

</body>
</html>
