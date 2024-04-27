<?php
if (isset($_POST['go_to_comparison'])) {
    header("Location: comparison.php");
    exit();
}

$cnx = new mysqli('localhost', 'mxxhxr', 'maahir2002', 'wsldatabase');
if ($cnx->connect_error)
    die('Connection failed: ' . $cnx->connect_error);

$query = 'SELECT * FROM products288';
$cursor = $cnx->query($query);

// Check if a product_id is set in the URL
if (isset($_POST['go_to_comparison'])) {
    redirect('comparison.php');
}

?>

<html>
<head>
    <title>My Dropshipping Website</title>
    <link rel="stylesheet" href="styles.css?v=<?php echo time(); ?>">
    <style>
    <?php include "styles.css" ?>
    </style>
</head>
<body>


<?php
while ($row = $cursor->fetch_assoc()) {
    $id = $row['product_id'];
    echo '<div class="product">';
    echo '<h3 class="product-info">Store Name</h3> <p class="info">' . $row['store_name'] .'</p>';
    echo '<h3 class="product-info">Product Name</h3> <p class="info">' . $row['product_name'] .'</p>';
    echo '<h3 class="product-info">Price</h3> <p class="info">$' . $row['price'] * 1.20  .'</p>';
    echo '<h3 class="product-info">Review Score</h3> <p class="info">' . $row['review_score'] .' Out Of 5</p>';
    echo '<img alt="Product Image" src="' . $row['image_url'] . '" class="product-image"></img>';
    echo '<h3 class="product-info">Description</h3> <p class="info">' . $row['description'] .'</p>';
    echo '<a href="comparison.php?id=' . $id . '">Go to Comparison</a>';
    echo '</div>';
    echo '<hr>';
}

$cnx->close();
?>

</body>
</html>




</body>
</html>
