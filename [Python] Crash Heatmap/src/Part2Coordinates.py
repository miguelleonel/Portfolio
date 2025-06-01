import requests
import json
import pandas as pd

MQkey = "aBc"   # get api keys
Googlekey = "aBc"
'''
FileCoord = "KINGSVILLE/MissingLatLong.csv" # manually feeding coordinates..
df = pd.read_csv(FileCoord)
count = 0
'''
def CoordFun(Street1, Street2, City):

	parameters = {"key": MQkey,
	"location": Street1 + "@" + Street2 + " " + City}

	Link = "http://www.mapquestapi.com/geocoding/v1/address"
	response = requests.get(Link, params = parameters)
	data = response.text
	dataJ = json.loads(data)['results']
	
	lat = (dataJ[0]['locations'][0]['latLng']['lat'])
	lng = (dataJ[0]['locations'][0]['latLng']['lng'])
	
    firstVal = lat
    secondVal = lng
    
	# Test for coordinates 'out of bounds'?
    
    '''
	if 27.46<=lat<=27.55 and -97.9<=lng<=-97.8:
		firstVal = lat
		secondVal = lng
	else:
		print("Error in coordinates! Running function again!!")
		print(str(lat)+"," + str(lng))
		CoordFun(Street1, Street2, City)


	location = Street1 + "@" + Street2 + " " + City
	# Manually feeding coordinates back to main function with MissingCoord.csv file.
	global count
	firstVal = df.Latitude[count].round(6)	# had to use round here, was extending decimal places?
	secondVal = df.Longitude[count].round(6) 
	print(count)
	count += 1
    '''
    
	return firstVal,secondVal