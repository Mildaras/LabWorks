SELECT
	CONCAT (UPPER (SUBSTR (sd.name, 1, 1)), SUBSTR (sd.name, 2)) as diena, 
	p.pavadinimas AS patiekalas,
	vl.name AS vartojimas,
	p.kalorijos,
	ksuma.suma as 'dienos kaloriju suma' 
FROM
	dienos AS d
	INNER JOIN patiekalai p ON p.id=d.fk_Patiekalasid
	LEFT JOIN savaites_dienos sd ON d.pavadinimas = sd.id_savaites_diena
	LEFT JOIN vartojimo laikai vl ON p.vartojimas = vl.id_vartojimo_laikas 
	LEFT JOIN
	(
		SELECT
			d.pavadinimas,
			SUM(p.kalorijos) as suma
		FROM dienos as d, patiekalai AS p 
		WHERE d.fk_Patiekalasid = p.id 
		GROUP BY d.pavadinimas
	) AS ksuma
	ON d.pavadinimas = ksuma.pavadinimas
WHERE
	ksuma.suma >= 0
ORDER BY d.pavadinimas
`