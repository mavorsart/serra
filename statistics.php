<?php
//verifico che provenga da arduino: password
	if($_POST["password"]=="serrarduino1994"){
		//leggo temperature
			$temp=$_POST['t'];
			$hum=$_POST['h'];
		//salvo ip nel database
			include("connessione.php");
			
			$sql="INSERT INTO statistiche VALUES(NOW(), '".$temp."', '".$hum."');";
			$ris=mysql_query($sql) or die ("Errore Query");

			mysql_close();
			
			echo $temp+"<br>";
			echo $hum;
	}
	else echo "Richiesta non autorizzata.";


?>