import pandas as pd
import numpy as np
from datetime import datetime
import matplotlib.pyplot as plt
import calendar
plt.style.use('Solarize_Light2')
myFile = "output.csv"
df = pd.read_csv(myFile)
# MUST INCLUDE RANGE OF MONTHS BY DIGIT. (ie. 5 = May)
# Change 6/6 vvv
monthRange = [11,12,1,2,3,4,5,6,7,8,9,10]	
# Change 6/6 ^^^
# Age analysis
avgAge = df.Age.mean().round(1)	# slightly differs from the dfAge.mean() in part 1?
maxAge = df.Age.max()
minAge = df.Age.min()
print('The min age of the driver is: ',minAge,'years old')
print('The max age of the driver is: ',maxAge,'years old')
print('The average age of the driver is: ',avgAge,'years old')
plt.figure() 
df.Age.hist(edgecolor='black', linewidth=1.2)
plt.title('Histogram of ages')
plt.xlabel('Age Groups')
plt.ylabel('Quantity')
plt.draw()

# Average time
x = pd.to_datetime(df.Time).values.astype(np.int64)
x = x.mean()
x = pd.to_datetime(x)
x = str(x.time())
x = datetime.strptime(x, "%H:%M:%S.%f")
avgTime = x.strftime("%I:%M %p")
print('The average time of an accident is:',avgTime)

# Bar graph of accidents by day of week
plt.figure() 
df.Day = pd.Categorical(df.Day, categories=
    ['SUN','MON','TUE','WED','THU','FRI','SAT'],
    ordered=True)
accidentsbyday = df.Day.groupby(df['Day'],sort=False).count().plot(kind='barh')
plt.gca().invert_yaxis()	# going from bar to barh, inverting axis makes sense.
plt.title('Accidents by Day of Week')
plt.xlabel('Number of accidents')
plt.ylabel('Day')
plt.draw()

DateTimeArr = pd.to_datetime(df['Date'] + ' ' + df['Time'])	# confusing method, but it works..

# Bar graph of accidents by hour
plt.figure() 
accidentsbyhour = DateTimeArr.groupby(DateTimeArr.dt.hour).count().plot(kind='bar')
plt.title('Accidents by Time of day')
plt.xlabel('Hour')
plt.ylabel('Number of accidents')
plt.draw()

# Number of accident per month
accidentsbymonth = DateTimeArr.groupby(DateTimeArr.dt.month).count()
accidentsbymonth.index=[calendar.month_name[x] for x in monthRange] # converts month digit to calendar month
print(accidentsbymonth.to_string()) # .to_string() removes 'dtype' on console output.

# plot accidents per month
plt.figure() 
accidentsbymonth.plot(kind='barh')
plt.gca().invert_yaxis()	# going from bar to barh, inverting axis makes sense.
plt.title('Accidents Throughout the Months')
plt.xlabel('Number of accidents')
plt.ylabel('Month')
plt.tight_layout()
for i, v in enumerate(accidentsbymonth):
	plt.text(v+.1, i+.15, str(v))

plt.show()
