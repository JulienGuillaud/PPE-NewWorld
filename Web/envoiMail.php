<?php
session_start();
if (isset($_SESSION['prodLogin']))
{
	header('location: index.php');
}
?>
<html>
<head>
	<title>Envoi mail</title>
	<meta charset="utf-8">
  	<link href="https://fonts.googleapis.com/css?family=Pacifico" rel="stylesheet">
  	<!-- <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.6.3/css/all.css" integrity="sha384-UHRtZLI+pbxtHCWp1t77Bi1L4ZtiqrqD80Kn4Z8NTSRyMA2Fd33n5dQ8lWUE00s/" crossorigin="anonymous"> -->
  	<link rel="stylesheet" type="text/css" href="formStyle.css">
  	<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.2.1/css/bootstrap.min.css" integrity="sha384-GJzZqFGwb1QTTN6wy59ffF1BuGJpLSa9DkKMp0DgiMDm4iYMj70gZWKYbI706tWS" crossorigin="anonymous">
</head>
<body>
	<div class="header">
		<a href="index.php" class="logo"><b>NEW-WORLD</b></a>
		<a href="index.php" class="navItem"><b>CONTACT</b></a>
<?php
if (!isset($_SESSION['prodLogin']) || !isset($_SESSION['cliLogin']))
{
	echo "<a href=\"connection.php\" class=\"navItem\"><b>CONNECTION</b></a>";
	echo "<a href=\"inscription.php\" class=\"navItem active\"><b>INSCRIPTION</b></a>";
}
else
{
	echo "<a href=\"deconnection.php\" class=\"navItem\"><b>DECONNECTION</b></a>";
	echo "<a href=\"gestionProducteurs.php\" class=\"navItem\"><b>GESTION</b></a>";
}
?>
		<a href="index.php" class="navItem"><b>ACCUEIL</b></a>
	</div>
	<h1 class="h1Titre">Envoi d'un mail de confirmation</h1>

	<p>Un mail de confirmation vous a été envoyé a <span id="spanRed"><?php echo $_POST['prodEmail'] ?></span>
	</p>

	<p>Si vous n'avez recu aucun mail d'ici 5min,
	<form method="POST" action="" style="text-align: left;">
		<input type="hidden" name="prodEmail" value="<?=$_POST['prodEmail']?>">
		<input type="hidden" name="prodNom" value="<?=$_POST['prodNom']?>">
		<input type="submit" class="boutonEnvoyer" value="cliquez ici">

	</form>
	</p>
	<?php
	include('connect.php');

	$reqIdProd='select entreID from Producteurs where prodNom=\''.$_POST['prodNom'].'\'';
	$resIdProd=mysqli_query($connect,$reqIdProd);
	$tabIdProd=mysqli_fetch_row($resIdProd);
	$idProd=$tabIdProd[0];
	$cle=sha1($idProd);
	echo $cle;


	$destinataire=$_POST["prodEmail"];
	$headers="From : newWorldJ.Guillaud.com";
	$sujet="Confirmation inscription newWorld !";
	$message="<h1>Confirmation inscription</h1>
		<p>Bonjour Mr/Mme.".$_POST['prodNom']."</p>
		<p>Cliquez sur ce bouton pour activer votre compte !</p>
		<a href='/var/www/html/newWorld/connection.php?cle=$cle&id=$idProd'><button style=\"padding: 5px; background-color: blue; border-radius: 10px;\">Confirmer le compte</button></a>";

	mail($destinataire, $sujet, $message, $headers);






?>
</body>
