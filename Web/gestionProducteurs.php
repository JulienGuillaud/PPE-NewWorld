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
		<a href="index.php" class="navItem"><b>ACCUEIL</b></a>

		<?php
		$reqInfoProd="select * from Producteurs inner join Ville on Producteurs.prodVille=Ville.VilleID where prodID=".$_SESSION['prodID'];
		$resInfoProd=mysqli_query($connect,$reqInfoProd);
		$tabInfo=mysqli_fetch_row($resInfoProd);

		?>
	</div>
	<div class='profile'>
		<h2><?php echo $tabInfo[1].' '.$tabInfo[2]?></h2>
		<table>
			<tr>
				<th>Login</th>
				<td><?php echo $tabInfo[3]?></td>
			</tr>
			<tr>
				<th>Tel Fixe</th>
				<td><?php echo $tabInfo[4]?></td>
			</tr>
			<tr>
				<th>Tel Portable</th>
				<td><?php echo $tabInfo[5]?></td>
			</tr>
			<tr>
				<th>Adresse</th>
				<td><?php echo $tabInfo[7]?> <?php echo $tabInfo[18]?></td>
			</tr>
			<tr>
				<th>Email</th>
				<td><?php echo $tabInfo[8]?></td>
			</tr>
		</table>
	</div>
	<div>
		<?php
		if($tabInfo[16]==NULL)
		{
			echo "<h4 style='float:left;'>Pour renseigner l'adresse de votre Porte Monais virtuel <h4> <form style='margin-left:10px; float:left;' method='POST' action='modifProfile.php'> <input type='submit' class='profileAjouter' value='cliquez ici' name='porteMonaie'></form>";

		}

		?>
	</div>
	<div style="float:right;">
		<?php
		for ( $i=0 ; $i < count($tabInfo) ; $i++)
		{
			echo '<?p>'.$i.' = '.$tabInfo[$i].'</p>';
		}

		?>
	</div>
</div>
</body>
<script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.6/umd/popper.min.js" integrity="sha384-wHAiFfRlMFy6i5SRaxvfOCifBUQy1xHdJ/yoi7FRNXMRBu5WHdZYu1hA6ZOblgut" crossorigin="anonymous"></script>
<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.2.1/js/bootstrap.min.js" integrity="sha384-B0UglyR+jN6CkvvICOB2joaf5I4l3gm9GU6Hc1og6Ls7i6U/mkkaduKaBhlAXv9k" crossorigin="anonymous"></script>
</html>
