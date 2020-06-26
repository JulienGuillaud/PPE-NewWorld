<?php
session_start();
?>
<html>
<head>
	<title>Accueil</title>

	<meta charset="utf-8">
	<link href="https://fonts.googleapis.com/css?family=Pacifico" rel="stylesheet">
	<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.6.3/css/all.css" integrity="sha384-UHRtZLI+pbxtHCWp1t77Bi1L4ZtiqrqD80Kn4Z8NTSRyMA2Fd33n5dQ8lWUE00s/" crossorigin="anonymous">
	<link rel="stylesheet" type="text/css" href="formStyle.css">
	<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.2.1/css/bootstrap.min.css" integrity="sha384-GJzZqFGwb1QTTN6wy59ffF1BuGJpLSa9DkKMp0DgiMDm4iYMj70gZWKYbI706tWS" crossorigin="anonymous">
</head>
<body>
	<div class="header">
		<a href="index.php" class="logo"><b>NEW-WORLD</b></a>
		<a href="index.php" class="navItem"><b>CONTACT</b></a>
<?php
if (isset($_SESSION['prodLogin']) || isset($_SESSION['cliLogin']))
{
	echo "<a href=\"deconnection.php\" class=\"navItem\"><b>DECONNECTION</b></a>";
	echo "<a href=\"gestionProducteurs.php\" class=\"navItem\"><b>GESTION</b></a>";
}
else
{
	echo "<a href=\"connection.php\" class=\"navItem\"><b>CONNECTION</b></a>";
	echo "<a href=\"inscription.php\" class=\"navItem\"><b>INSCRIPTION</b></a>";
}
?>
		<a href="index.php" class="navItem active"><b>ACCUEIL</b></a>
	</div>
	<div>
		<h1>Accueil</h1>

		<p>NewWorld est un site d'achat/livraison de produits locaux en points relais partenaires</p>
	</div>
</body>
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.6/umd/popper.min.js" integrity="sha384-wHAiFfRlMFy6i5SRaxvfOCifBUQy1xHdJ/yoi7FRNXMRBu5WHdZYu1hA6ZOblgut" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.2.1/js/bootstrap.min.js" integrity="sha384-B0UglyR+jN6CkvvICOB2joaf5I4l3gm9GU6Hc1og6Ls7i6U/mkkaduKaBhlAXv9k" crossorigin="anonymous"></script>
</html>
