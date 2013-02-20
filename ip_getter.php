<?php
//verifico che provenga da arduino: password
	if($_POST["password"]=="serrarduino1994"){
		//leggo ip 
			$ip_p=$_SERVER['REMOTE_ADDR'];
			$ip_l=$_POST["local_ip"];
		//salvo ip nel database
			include("connessione.php");
			
			$sql="INSERT INTO ip_address (ip_date,ip_public,ip_local) VALUES(NOW(),'".$ip_p."','".$ip_l."');";
			$ris=mysql_query($sql) or die ("Errore Query");

			mysql_close();
			
			echo $ip_p;
			echo $ip_l;
	}
	else echo "Richiesta non autorizzata.";


?>
 