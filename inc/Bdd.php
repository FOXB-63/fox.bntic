<?php

class Bdd {
    private $connection = false;				//Instance PDO	
    private $sql = '';							//Dernière requête SQL executée

    /**	Fonction Constructeur    	
    Desc 	:	Initialise la connexion    	
    Params 	:	(string)$Serveur = Adresse du serveur MySQL    	
                            (string)$Utilisateur = Nom d'utilisateur de la base MySQL    	
                            (string)$MotDePasse = Mot de passe MySQL    	
                            (string)$BaseDeDonnees = Nom de la base de données    	
    Return	:	Void        	
    */
    public function __construct()
    {
        try {
            //On instancie l'objet PDO et on se connecte à la base
            $stringcns = "mysql:host=" . SRVNAME . ";dbname=" . SRVBDD . "; charset=utf8";
            $this->connection = new PDO($stringcns, SRVUTS, SRVPWD, array(PDO::ATTR_PERSISTENT => true));
        } catch (PDOException $e) {
            
        }
    }

    /**	Fonction LastInsertId
    #	Desc	:	Retourne l'id du dernier enregistrement inseré
    Params	:	None
    Return	:	(int)ID du dernier enregistrement inséré */
    
    public function LastInsertId()
    {
            //Requête permettant de récupérer le dernier id inséré
            $sql = 'SELECT LAST_INSERT_ID() as last_id';
            $query = $this->connection->query($sql);
            //On retourne le résultat de la requête
            return $query->fetchColumn();
    }

    /**	Fonction Query
    Desc	:	Execute une requête SQL
    Params	:	(string)$sql = Requête SQL
    Return	:	(int)Nombre d'enregistrements affectés par la requête
   */
    public function Query($Sql)
    {
            //On enregistre la requête pour pouvoir la ressortir au besoin
            $this->sql = $Sql;
            try {
                    //On execute la requête
                    $query = $this->connection->exec($this->sql);
                    return $query;	//Sinon on renvoie le résultat de la requête (nombre d'enregistrements affectés)
            } catch(Exception $e) {
                    return false;
            }
    }

    public function exeQuery($prepare, $tableau)
    {
            //On enregistre la requête pour pouvoir la ressortir au besoin
            $this->sql = $prepare;
            try {
                    //On execute la requête
                    $obcon = $this->connection;
                    $exe = $obcon->prepare($prepare);
                    $resultat = $exe->execute($tableau);
                    return $resultat;	//Sinon on renvoie le résultat de la requête (nombre d'enregistrements affectés)

            } catch(Exception $e) {
                    return false;
            }
    }

    /** Fonction Query2Array
    Desc	:	Retourne sous forme de tableau le résultat d'une requête de sélection
    Params	: 	(string)$sql = Requête SQL
    Return	:	(array)Résultat de la requête, sinon false en cas d'erreur
    */
    public function Query2Array($Sql)
    {
        //On enregistre la requête pour pouvoir la ressortir au besoin
        $this->sql = $Sql;

        try {
            //On execute la requête
            $query = $this->connection->query($this->sql);
            return $query->fetchAll(PDO::FETCH_ASSOC);//}//Sinon on retourne le tableau de résultat				
        } catch (Exception $e) {
            return false;
        }
    }

}
