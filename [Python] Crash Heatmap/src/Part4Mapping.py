import folium
from folium import plugins
from folium.plugins import HeatMap,HeatMapWithTime
import webbrowser	# functionality depends on python environment, tested on Ubuntu+Geany.
import pandas as pd
myFile = "output.csv"
df = pd.read_csv(myFile)
myLocation = [df.Latitude.mean(), df.Longitude.mean()]

# Simple map creation with markers.
myMap = folium.Map(myLocation, zoom_start=13) # adjust zoom to specific application.
dftemp = df['Date'].astype(str)+',\n'+df['Time'].astype(str)
for index, row in df.iterrows():
    folium.Marker([row['Latitude'], row['Longitude']], popup=dftemp[index]).add_to(myMap)
myMap.save("myMap.html")

# map creation with automatically clustered groups.
myMap = folium.Map(myLocation, zoom_start=13) # clean map.
myMap = plugins.MarkerCluster().add_to(myMap)
for index, row in df.iterrows():
    folium.Marker([row['Latitude'], row['Longitude']], popup=dftemp[index]).add_to(myMap)

myMap.save("myMap2.html")

# heat map

myMap = folium.Map(myLocation, zoom_start=13) # adjust zoom to specific application.
#dftemp = df.dropna(axis=0, subset=['Latitude','Longitude'])
dftemp = df[['Latitude','Longitude']]
dftemp = [[row['Latitude'],row['Longitude']] for index, row in dftemp.iterrows()]
HeatMap(dftemp).add_to(myMap)
myMap.save("myMap3.html")


webbrowser.open("myMap.html")
webbrowser.open("myMap2.html")
webbrowser.open("myMap3.html")

# HeatMapWithTime sort of sparse for the data being used for Kingsville.
'''
DateTimeArr = pd.to_datetime(df['Date'] + ' ' + df['Time'])	# used for heatmapwithtime

hour_list = [ [] for _ in range(24) ]
for lat,log,hour in zip(df.Latitude,df.Longitude,DateTimeArr.dt.hour):
    hour_list[hour].append([lat,log]) 
index = [str(i)+' Hours' for i in range(24)]
HeatMapWithTime(hour_list, index).add_to(myMap)
myMap.save("myMap4.html")
'''