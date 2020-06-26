<?php
session_start();
include('connect.php');

//if (isset($_GET['id']))

if (isset($_POST['prodConnectionLogin']) && isset($_POST['prodConnectionMdp']))
{
	$req="select count(*) from Producteurs where prodLogin='".$_POST['prodConnectionLogin']."' and prodPassword=password('".$_POST['prodConnectionMdp']."')";
	$res=mysqli_query($connect,$req);
	$tabInfo=mysqli_fetch_row($res);
	if ($tabInfo[0]==1)
	{
		$reqConfirm="select count(*) from Producteurs where prodLogin='".$_POST['prodConnectionLogin']."' and prodPassword=password('".$_POST['prodConnectionMdp']."') and prodConfirme=1";
		$resConfirm=mysqli_query($connect,$reqConfirm);
		$tabInfoConfirm=mysqli_fetch_row($resConfirm);
		if ($tabInfoConfirm[0]==1)
		{
			$reqID="select prodID from Producteurs where prodLogin='".$_POST['prodConnectionLogin']."' and prodPassword=password('".$_POST['prodConnectionMdp']."') and prodConfirme=1";
			$resID=mysqli_query($connect,$reqID);
			$tabInfoID=mysqli_fetch_row($resID);

			$_SESSION['prodID']=$tabInfoID[0];
			$_SESSION['prodLogin']=$_POST['prodConnectionLogin'];
			$adresseMailConfirme=1;
		}
		else
		{
			$adresseMailConfirme=0;
		}
	}
}

if (isset($_GET['cle']) && isset ($_GET['id']))
{
	//verification clé
}

if (isset($_SESSION['prodLogin']))
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
if (!isset($_SESSION['prodLogin']) || !isset($_SESSION['cliLogin']))
{
	echo "<a href=\"connection.php\" class=\"navItem active\"><b>CONNECTION</b></a>";
	echo "<a href=\"inscription.php\" class=\"navItem\"><b>INSCRIPTION</b></a>";
}
else
{
	echo "<a href=\"deconnection.php\" class=\"navItem\"><b>DECONNECTION</b></a>";
	echo "<a href=\"gestionProducteurs.php\" class=\"navItem\"><b>GESTION</b></a>";
}
?>
		<a href="index.php" class="navItem"><b>ACCUEIL</b></a>
	</div>

	<div>
	<form method="POST" action="">
		<h1 class="h1Titre">Connection</h1><br>
		<div class="center-block form">

		     <p>
				<i class="fas fa-address-card"></i>
				<input class="inputCss" type="text" name="prodConnectionLogin" placeholder="Login" oninput="toutVerif()" maxlength="30">
				<br>
		     </p>
		     <p>
				<i class="fas fa-lock prefix grey-text"></i>
				<input class="inputCss" type="password" name="prodConnectionMdp" placeholder="Password" oninput="toutVerif()" maxlength="30">
				<br>
		     </p>
		</div>
		<div class="form">
<?php
if (isset($adresseMailConfirme))
{
	if ($adresseMailConfirme==0)
	{
		echo '<p class="centrer" style="color:red;">Adresse email non verifié.</p>';
	}
}
?>


		</div>
		<div class="form">
		      <p>
			<input class="boutonEnvoyer" id="boutonEnvoyer" type="submit" value="Connection">
		      </p>

		</div>
	</div>
</body>
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.6/umd/popper.min.js" integrity="sha384-wHAiFfRlMFy6i5SRaxvfOCifBUQy1xHdJ/yoi7FRNXMRBu5WHdZYu1hA6ZOblgut" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.2.1/js/bootstrap.min.js" integrity="sha384-B0UglyR+jN6CkvvICOB2joaf5I4l3gm9GU6Hc1og6Ls7i6U/mkkaduKaBhlAXv9k" crossorigin="anonymous"></script>
</html>
