import pandas as pd
from Part2Coordinates import CoordFun


# Change 1/6 vvv
City = "Kingsville, Texas"	
# Change 1/6 ^^^
# Change 2/6 vvv
FileCrash = "KINGSVILLE/extract_public_2018_20211201182939332_79430_20201101-20211031_KINGSVILLE/extract_public_2018_20211201182939_crash_20201101-20211031_KINGSVILLE.csv"
# Change 2/6 ^^^
dfCrash = pd.read_csv(FileCrash)	

dfCrash.Crash_ID.drop_duplicates(inplace=True)	# should drop duplicate CrashIDs, has not happened in testing.
# Change 3/6 vvv
FileAge = "KINGSVILLE/extract_public_2018_20211201182939332_79430_20201101-20211031_KINGSVILLE/extract_public_2018_20211201182939_primaryperson_20201101-20211031_KINGSVILLE.csv"
# Change 3/6 ^^^
field = ['Prsn_Age']
dfAge = pd.read_csv(FileAge, usecols=field) 
dfAge.fillna(dfAge.mean().round(0), inplace=True) # inplace here means no "dfAge ="; round instead of default truncate.
dfAge = dfAge.astype(int)

num = dfCrash['Latitude'].isnull().sum()
DataLength = len(dfCrash.index)
print('The percent of data with missing lat/long values is: ', (num/DataLength*100).round(2),'%')
# deleting NaN lat/long values.
# Change 4/6 vvv
dfCrash = dfCrash[dfCrash['Latitude'].notna()] # comment out depending on using part2 function (broken)
# Change 4/6 ^^^
num = dfCrash['Latitude'].isnull().sum()
print('After removing rows with missing lat/long - percent is: ', (num/DataLength*100).round(2),'%')
dfCrash = dfCrash.fillna('')
dfCrash['Street1'] = dfCrash['Rpt_Block_Num'].astype(str)+' '+dfCrash['Rpt_Street_Pfx']+' '+dfCrash['Rpt_Street_Name']+' '+dfCrash['Rpt_Street_Sfx']
dfCrash['Street2'] = dfCrash['Rpt_Sec_Block_Num'].astype(str)+' '+dfCrash['Rpt_Sec_Street_Pfx']+' '+dfCrash['Rpt_Sec_Street_Name']+' '+dfCrash['Rpt_Sec_Street_Sfx']
# reference elements: dfCrash.Street1[0]

for i in range(0,DataLength):
	if (dfCrash.Latitude[i] == ''):
		dfCrash.iloc[i, dfCrash.columns.get_loc('Latitude')],dfCrash.iloc[i, dfCrash.columns.get_loc('Longitude')] = CoordFun(dfCrash.Street1[i],dfCrash.Street2[i],City)
	# could probably fix but comment out if 'change 4/6' also commented out (ie. not deleting NaN lat/long val)
	# Change 5/6 vvv
	else:
		break
	# Change 5/6 ^^^
df = pd.concat([dfCrash, dfAge], axis=1, join='inner')
df = df.rename(columns={'Crash_Date': 'Date', 'Crash_Time': 'Time', 'Day_of_Week': 'Day', 'Prsn_Age': 'Age'})
header = ['Date','Time','Day','Age','Latitude','Longitude','Street1','Street2']
df.to_csv('output.csv', columns = header,index=False)