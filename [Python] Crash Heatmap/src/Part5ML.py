import pandas as pd
import matplotlib.pyplot as plt
from sklearn.cluster import MiniBatchKMeans,KMeans
import seaborn as sns	# pip3 install seaborn
sns.set_theme(style='ticks')
myFile = "output.csv"
df = pd.read_csv(myFile)

# Mini Batch K Means
df = df.loc[:,['Latitude','Longitude','Age']]
kmeans = MiniBatchKMeans(n_clusters=5, random_state=0, batch_size=6)
df['Cluster'] = kmeans.fit_predict(df)
df['Cluster'] = df['Cluster'].astype('int')
print(df.head())

plt.rc('figure', autolayout=True)
plt.rc('axes')
sns.relplot(x='Longitude',y='Latitude', hue = 'Cluster', data = df, height = 6)
plt.draw()


# Traditional K Means
# Pseudo Code...
# use of this ML could be tested against better data, like combining Dallas and Ft Worth
# enough to have thousands of entries, where weather conditions vary more often.
# test against weather condition versus area? or time of day/day of week?
'''
df = df.loc[:,['City','Day']]
grouped = pd.get_dummies(df['Day'])
grouped['City'] = df['City']
grouped = grouped.groupby('City').sum().reset_index()
# after grouping, reassign/drop identifier
newIdent = grouped[['City']]
grouped = grouped.drop('City', axis=1)
newIdent['cluster'] = kmeans.labels_
kmeans2 = KMeans(n_clusters=4, random_state=0).fit(grouped)
'''
plt.show()
