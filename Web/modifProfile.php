<?php
session_start();
include('connect.php');

if (!isset($_SESSION['prodLogin']))
{
	header('location: index.php');
}
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
if (!isset($_SESSION['prodLogin']))
{
	echo "<a href=\"connection.php\" class=\"navItem\"><b>CONNECTION</b></a>";
	echo "<a href=\"inscription.php\" class=\"navItem\"><b>INSCRIPTION</b></a>";
}
else
{
	echo "<a href=\"deconnection.php\" class=\"navItem\"><b>DECONNECTION</b></a>";
	echo "<a href=\"gestionProducteurs.php\" class=\"navItem active\"><b>GESTION</b></a>";
}
?>
		<a href="index.php" class="navItem"><b>ACCUEIL</b></a>
</div>
<div>
<?php
$reqInfoProd="select * from Producteurs  where prodID=".$_SESSION['prodID'];
$resInfoProd=mysqli_query($connect,$reqInfoProd);
$tabInfo=mysqli_fetch_row($resInfoProd);

if (isset($_POST['porteMonaie']))
{
	echo "<form method='POST' action=''>
	<input type='text' name='porteMonaieInput' placeholder='Clé Porte Monaie'>
	<input type='submit' name='submitPorteMonaie'>
	</form>
";

}

if (isset($_POST['submitPorteMonaie']))
{
	$reqPorteMonaie="update Producteurs set prodPaiementCle='".$_POST['porteMonaieInput']."'";
	$resPorteMonaie=mysqli_query($connect,$reqPorteMonaie);
}
?>

	</div>
</body>
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.6/umd/popper.min.js" integrity="sha384-wHAiFfRlMFy6i5SRaxvfOCifBUQy1xHdJ/yoi7FRNXMRBu5WHdZYu1hA6ZOblgut" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.2.1/js/bootstrap.min.js" integrity="sha384-B0UglyR+jN6CkvvICOB2joaf5I4l3gm9GU6Hc1og6Ls7i6U/mkkaduKaBhlAXv9k" crossorigin="anonymous"></script>
</html>


