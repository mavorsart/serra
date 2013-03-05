<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title>Prova statistiche</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
</head>

<body>

<h2>Prova statistiche</h2>
<p>Ecco il microclima presente:
<?php

		//leggo ip dal database
			include("connessione.php");
			
			$sql="SELECT stat_t,stat_h FROM statistiche ORDER BY stat_date DESC;";
			$ris=mysql_query($sql) or die ("Query fallita.");
			echo "<ul>";
				while($riga=mysql_fetch_array($ris)){
					echo "<li>T = ".$riga['stat_t']." e H = ".$riga['stat_h']."</li>";
				}
			echo "</ul>";
			
			mysql_close();
		


?>
</p>
</body>
</html>