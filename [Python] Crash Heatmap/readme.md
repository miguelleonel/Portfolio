Final Project for Engineering Programming II course (EE 5453).

In short, this project made use of publicly requested data from CRIS, a crash report database maintained by the Texas DoT, and dynamically parsed data to generate a heatmap from data supplied. 

Starting from this: 
<img src="https://raw.githubusercontent.com/miguelleonel/Portfolio/refs/heads/main/%5BPython%5D%20Crash%20Heatmap/Output/Figures/FormattedData.png" width="800">

To end up with this:
<img src="https://raw.githubusercontent.com/miguelleonel/Portfolio/refs/heads/main/%5BPython%5D%20Crash%20Heatmap/Output/Figures/KingsvilleHeatmap.png" width="640">


Initial data was parsed and modified, where only relevant information was taken. 
Lines with only street information were retreived for their coordinates with Google maps API. 
"output.csv" shows what the modified data looks like, this was what was used to create visual aids like the graphs and heatmaps. 

"Term Project Requirements.pdf" explains the course requirements, "Powerpoint - Crash Data Analysis Heatmap.pdf" is the presentation used to explain the overall project. 

Note: HTML was the best method for keeping the map interactive, as converting to figure/PDF did not allow for the pan/zoom feature. 
Have to download to view properly, as Github shows the html code that was automatically created.

Video presenting project for course (16 minutes):
https://youtu.be/jZwpR8pVERA
