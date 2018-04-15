# HU-Vision-1718-Base
Assessment for course Vision (Hogeschool Utrecht). Teammembers: Kiet van Osnabrugge, Wiebe van Breukelen

## Schedule
[Schedule](https://hogeschoolutrecht-my.sharepoint.com/:x:/g/personal/wiebe_vanbreukelen_student_hu_nl/EbH97KKLpkRPtmnqgkJ9acQBuBZ5KSvSXri5fRnnM_sNNQ?e=iXx4n3)

## Ideas

Waar zouden we op kunnen testen?

- Snelheid (dit zou bijvoorbeeld in een tijdseenheid kunnen, of doormiddel van benchmarking (hoeveel bewerkingen binnen één seconde?) Hierbij zouden we onze eigen implementatie tegen de standaard implementatie kunnen testen.
- Geheugengebruik
- Robuustheid Wat gebeurt er als we ruis gaan aanbregen? Kunnen we hierop inspelen?


Het implementatieplan dient een afweging tussen verschillende edge detection methoden te bevatten.
Standaard wordt er edge detection op basis van de Laplacian operator/kernel toegepast.
Mogelijke edge detection methoden:
- Sobel: operator/kernel https://en.wikipedia.org/wiki/Sobel_operator
- Canny: (verwerkt uitkomst van Sobel dmv filter). Hierbij worden er verschillende eisen gesteld aan bijvoorbeeld de vectorrichting, vectorlengte, etc. Hierdoor kunnen er edges uitgefilterd worden. https://nl.wikipedia.org/wiki/Canny-randzoeker

Er zullen vast meer edge detection methoden bestaan maar hier dient nog onderzoek naar worden gedaan!
Uiteindelijk gaat het erom dat onze keuze goed onderbouwd wordt aan de hand van een hypothese (wat verwacht ik?). Deze hypothese slaat dan ook weer terug op de twee gekozen meetrapport onderwerpen.

## Implementation plan
[Document](https://github.com/wvanbreukelen/HU-Vision-1718-Base/blob/master/implementatieplannen/working/Implementatieplan.docx)

