<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="utf-8">

  <title>Tinklu LAB2</title>
  <meta name="description" content="Tinklu 2 laboras">

  <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">

</head>

<body>
	<div class='container'>
   <?php
 //https://auth-db240.hostinger.com/index.php?db=u429721638_tinklai
	$dbServer = "localhost";
	$dbUsername = "u429721638_tink";
	$dbPassword = "yeeet";
	$dbName = "u429721638_tinklai";
	$conn = mysqli_connect($dbServer, $dbUsername, $dbPassword, $dbName);
	
	if($conn == false)
	{
		//Jeigu prisijungimas blogas, stabdo kodą.
		die("Prisijungimas prie duomenu bazes buvo blogas<br>".mysqli_connect_error());
	}


	$sql = "SELECT * FROM vardaspavarde";
	$result = $conn->query($sql);

	if ($result->num_rows > 0) 
	{
		echo "<table class='table table-striped' style='width:100%'>";
		echo "<tr>";

		echo "<th>Nr</th>";
		echo "<th>Kas siuntė</th>";
		echo "<th>Siuntėjo e-paštas</th>";
		echo "<th>Gavėjas</th>";
		echo "<th>Data (IP)</th>";
		echo "<th>Žinutė</th>";

		echo "</tr>";
	    while($row = $result->fetch_assoc()) 
	    {
	    	echo "<tr>";
	        echo "<td>".$row['id']."</td>";
	    	echo "<td>".$row['vardas']."</td>";
	    	echo "<td>".$row['epastas']."</td>";
	    	echo "<td>".$row['kam']."</td>";
	    	echo "<td>".$row['data']."(".$row['ip'].")</td>";
	    	echo "<td>".$row['zinute']."</td>";
	    	echo "</tr>";
	    }
	    echo "</table>";
	} 
	else 
	{
	    echo "0 rezultatų";
	}


?> 

<form method='POST'>
  <div class="form-row">
  	<div class="col">
    	<label for="vardasLabel"><b>Siuntėjo vardas</b></label>
	    <input class="form-control" id="vardasLabel" name='vardas'>
	</div>

	<div class="col">
    	<label for="emailLabel"><b>Siuntėjo e-paštas:</b></label>
    	<input class="form-control" id="emailLabel" name='email'>
	</div>
	<div class="col">
   		<label for="kamLabel"><b>Kam skirta:</b></label>
    	<input class="form-control" id="kamLabel" name='kam'>
    </div>
  </div>
  <label for="exampleFormControlTextarea2"><b>Žinutė:</b></label>
  <textarea class="form-control rounded-0" name='zinute' id="exampleFormControlTextarea2" rows="3"></textarea>
   
  <button name='submit' type="submit" class="btn btn-primary">Siųsti</button>
</form>

<?php

if(isset($_POST['submit']))
{
	date_default_timezone_set("Europe/Vilnius");
	$siuntejoVardas = mysqli_real_escape_string($conn, $_POST['vardas']);
	$siuntejoPastas = mysqli_real_escape_string($conn, $_POST['email']);
	$kamSiunciam = mysqli_real_escape_string($conn, $_POST['kam']);
	$zinute = mysqli_real_escape_string($conn, $_POST['zinute']);
	
	$laikas = date('Y-m-d H:i:s');
	$ipAdresas = $_SERVER['REMOTE_ADDR'];

	if(empty($siuntejoVardas) || empty($siuntejoPastas) || empty($kamSiunciam) || empty($zinute))
	{
		echo '<div class="alert alert-danger" role="alert">
  Užpildykite visus laukus!
</div>';
	}
	else
	{
				$sqlInsert = "INSERT INTO vardaspavarde (vardas, epastas, kam, data, ip, zinute)
VALUES ('$siuntejoVardas', '$siuntejoPastas', '$kamSiunciam', '$laikas', '$ipAdresas', '$zinute')";
		mysqli_query($conn, $sqlInsert);
		echo '<div class="alert alert-success" role="alert">
		  Įkelta! :)
		</div>';
	}
}

?>

<form method='POST'>

<input name='istrintVarda' placeholder='Vardas kuri istrinti'>
<button name='istrinti' type="submit" class="btn btn-danger">Siųsti</button>

</form>

</div>


<?php
	if(isset($_POST['istrinti']))
	{
		$input = mysqli_real_escape_string($conn, $_POST['istrintVarda']);
		$sqlDelete = "DELETE FROM vardaspavarde WHERE vardas='$input'";
		mysqli_query($conn, $sqlDelete);
	}
?>

<script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js" integrity="sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1" crossorigin="anonymous"></script>
<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js" integrity="sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM" crossorigin="anonymous"></script>
</body>
</html>