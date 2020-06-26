<?php
session_start();
?>
<html>
<head>
	<title>Recap</title>
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
		if (!isset($_SESSION['prodLogin']))
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
</head>
<body>
	<h1 class="h1Titre">Inscription Producteur Recap</h1>
	<div class="row justify-content-md-center" style="margin-top:35px;">
		<div class="col-3">
			<form method="POST" action="envoiMail.php">
				<p>
					<i class="fas fa-address-card"></i>
					<input class="inputCss" type="text"readonly name="prodNom" value="<?=$_POST['prodNom']?>">
					<br>
				</p>
				<p>
					<i class="fas fa-address-card"></i>
					<input class="inputCss" type="text" readonly name="prodPrenom" value="<?=$_POST['prodPrenom']?>">
					<br>
				</p>
				<p>
					<i class="fas fa-phone"></i>
					<input class="inputCss" type="tel" readonly name="prodTelFixe" value="<?=$_POST['prodTelFixe']?>">
					<br>
				</p>
				<p>
					<i class="fas fa-phone"></i>
					<input class="inputCss" type="tel" readonly name="prodTelPortable" value="<?=$_POST['prodTelPortable']?>">
					<br>
				</p>
				<div class="form">
					<p>
						<i class="fas fa-home"></i>
						<input class="inputCss" type="text"readonly name="prodAdressePostale" value="<?=$_POST['prodAdressePostale']?>">
					</p>
				</div>
				<div class="form">
					<p>
						<i class="fas fa-home"></i>
						<input class="inputCss" type="text" readonly name="prodCp" value="<?=$_POST['prodCp']?>">
					</p>
				</div>
				<div class="form">
					<p>
						<i class="fas fa-home"></i>
						<input class="inputCss" type="text" readonly name="prodVille" value="<?=$_POST['prodVille']?>">
					</p>
				</div>
			</div>
			<div class="col-">
				<div class="form">
					<p class="checkbox activite"><i class="fas fa-tasks"></i> Activité :</p>
				</div>
				<div class="form">
					<div>
						<input type="checkbox"  disabled name="fruits" <?php if(isset($_POST['fruits']) && $_POST['fruits']=='on'){echo 'checked';}?>>
						<label class="checkbox" for="fruits">Fruits</label>
						<br>
						<input type="checkbox" disabled name="legumes" <?php if(isset($_POST['legumes']) && $_POST['legumes']=='on'){echo 'checked';}?>>
						<label class="checkbox" for="legumes">Legumes</label>
						<br>
						<input type="checkbox" disabled name="viandes" <?php if(isset($_POST['viandes']) && $_POST['viandes']=='on'){echo 'checked';}?>>
						<label class="checkbox" for="viandes">Viandes</label>
						<br>
						<input type="checkbox" disabled name="laitages" <?php if(isset($_POST['laitages']) && $_POST['laitages']=='on'){echo 'checked';}?>>
						<label class="checkbox" for="laitages">Laitages</label>
						<br>
						<input type="checkbox" disabled name="services" <?php if(isset($_POST['services']) && $_POST['services']=='on'){echo 'checked';}?>>
						<label class="checkbox" for="services">Services</label>
						<br>
						<input type="checkbox" disabled name="autre" id="autre" <?php if(isset($_POST['autre']) && $_POST['autre']=='on'){echo 'checked';}?>>
						<label class="checkbox" for="autre" onclick="fonctionAutre()">Autre</label>
						<br>
						<input type="text" name="autreInput" id="autreInputId" readonly <?php if(isset($_POST['autre']) && $_POST['autre']=='on'){echo 'style="visibility:visible;"';} else{echo 'style="visibility:hidden;"';}?> value="<?=$_POST['autreInput']?>">


						</p>
					</div>
				</div>
			</div>
			<div class="col-3">
				<div class="form">
					<p>
						<i class="fas fa-industry"></i>
						<input class="inputCss" type="text" readonly name="prodSiretSiren" value="<?=$_POST['prodSiretSiren']?>">
					</p>
				</div>

				<div class="form">
					<p>
						<i class="fas fa-industry"></i>
						<input class="inputCss" type="text" readonly name="nomEntreprise" id="nomEntreprise" value="<?=$_POST['nomEntreprise']?>">
					</p>
				</div>


				<div class="form">
					<p>
						<i class="fas fa-user prefix grey-text"></i>
						<input class="inputCss" type="text" readonly name="prodLogin" value="<?=$_POST['prodLogin']?>">
					</p>
				</div>
				<div class="form">
					<p>
						<i class="fas fa-envelope prefix grey-text"></i>
						<input class="inputCss" type="email" readonly name="prodEmail" value="<?=$_POST['prodEmail']?>">
						<br>
					</p>
				</div>
				<div class="form">
					<p>
						<i class="fas fa-lock prefix grey-text"></i>
						<input class="inputCss" type="password" readonly name="prodMotDePasse" value="<?=$_POST['prodMotDePasse']?>">
						<br>
					</p>
				</div>
				<div class="form">
					<p>
						<input type="submit" class="boutonEnvoyer" id="boutonEnvoyer" value="Envoyer le mail de confirmation">
					</p>
				</div>
			</div>
		</div>
	</form>
</div>
<?php
include ('connect.php');
if(isset($_POST['prodNom']) &&
isset($_POST['prodPrenom']) &&
isset($_POST['prodTelFixe']) &&
isset($_POST['prodTelPortable']) &&
isset($_POST['prodAdressePostale']) &&
isset($_POST['prodCp']) &&
isset($_POST['prodVille']) &&
isset($_POST['prodSiretSiren']) &&
isset($_POST['nomEntreprise']) &&
isset($_POST['prodLogin']) &&
isset($_POST['prodEmail']) &&
isset($_POST['prodMotDePasse'])
)
{
	$reqSqlEntreprise='insert into Entreprise (entreLib,entreSIRET,entreConfirm) VALUES (\''.$_POST['nomEntreprise'].'\',\''.$_POST['prodSiretSiren'].'\',false)';
	//echo $reqSqlEntreprise;
	$resEntreprise=mysqli_query($connect,$reqSqlEntreprise);

	$reqIdEntreprise='select entreID from Entreprise where entreSIRET=\''.$_POST['prodSiretSiren'].'\'';
	$resIdEntreprise=mysqli_query($connect,$reqIdEntreprise);
	$tabIdEntreprise=mysqli_fetch_row($resIdEntreprise);
	$idEntreprise=$tabIdEntreprise[0];

	$password=($_POST['prodMotDePasse']);
	$idProducteur=time();

	if (isset($_POST['autre']))
	{
		if($_POST['autre']=='on')
		{
			$reqSqlProducteur='insert into Producteurs(prodID,prodNom,prodPrenom,prodLogin,prodTelPortable,prodTelFix,prodVille,prodRue,prodEmail,prodPassword,prodActivite,prodConfirme,entreID) VALUES (\''.$idProducteur.'\',\''.$_POST['prodNom'].'\',\''.$_POST['prodPrenom'].'\',\''.$_POST['prodLogin'].'\',\''.$_POST['prodTelPortable'].'\',\''.$_POST['prodTelFixe'].'\',\''.$_POST['prodVille'].'\',\''.$_POST['prodAdressePostale'].'\',\''.$_POST['prodEmail'].'\',\''.$password.'\',\''.$_POST['autreInput'].'\',false,\''.$idEntreprise.'\')';

		}
	}
	else
	{
		$reqSqlProducteur='insert into Producteurs(prodID,prodNom,prodPrenom,prodLogin,prodTelPortable,prodTelFix,prodVille,prodRue,prodEmail,prodPassword,prodConfirme,entreID) VALUES
		(\''.$idProducteur.'\',\''.$_POST['prodNom'].'\',\''.$_POST['prodPrenom'].'\',\''.$_POST['prodLogin'].'\',\''.$_POST['prodTelPortable'].'\',\''.$_POST['prodTelFixe'].'\',\''.$_POST['prodVille'].'\',\''.$_POST['prodAdressePostale'].'\',\''.$_POST['prodEmail'].'\',password(\''.$_POST['prodMotDePasse'].'\'),false,\''.$idEntreprise.'\')';

	}
	//echo "<p> $reqSqlProducteur </p>";
	$resProducteur=mysqli_query($connect,$reqSqlProducteur);


	$prodCle=sha1(time());
	$reqCle="update Producteurs set prodCle='".$prodCle."' where prodID=".$idProducteur;
	$resCle=mysqli_query($connect,$reqCle);

	if (isset($_POST['fruits']))
	{
		if($_POST['fruits']=="on")
		{
			$reqFruits='insert into Activite (prodID,sectID) VALUES (\''.$idProducteur.'\',\'1\')';
			$resFruits=mysqli_query($connect,$reqFruits);
			//echo "<p> $reqFruits </p>";
		}
	}

	if (isset($_POST['legumes']))
	{
		if($_POST['legumes']=="on")
		{
			$reqLegumes='insert into Activite (prodID,sectID) VALUES (\''.$idProducteur.'\',\'2\')';
			$resLegumes=mysqli_query($connect,$reqLegumes);
			//echo "<p> $reqLegumes </p>";
		}
	}

	if (isset($_POST['viandes']))
	{
		if($_POST['viandes']=="on")
		{
			$reqViandes='insert into Activite (prodID,sectID) VALUES (\''.$idProducteur.'\',\'3\')';
			$resViandes=mysqli_query($connect,$reqViandes);
			//echo "<p> $reqViandes </p>";
		}
	}

	if (isset($_POST['laitages']))
	{
		if($_POST['laitages']=="on")
		{
			$reqLaitages='insert into Activite (prodID,sectID) VALUES (\''.$idProducteur.'\',\'4\')';
			$resLaitages=mysqli_query($connect,$reqLaitages);
			//echo "<p> $reqLaitages </p>";
		}
	}

	if (isset($_POST['services']))
	{
		if($_POST['services']=="on")
		{
			$reqServices='insert into Activite (prodID,sectID) VALUES (\''.$idProducteur.'\',\'5\')';
			$resServices=mysqli_query($connect,$reqServices);
			//echo "<p> $reqServices </p>";
		}
	}
}

else




?>
</body>
