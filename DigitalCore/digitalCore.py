def conglomerateData(files):

	newLines = []

	with open(files[0], "r") as firstFile:

		for line in firstFile:

			newLines.append("")

	for file in files:

		with open(file, "r") as dataFile:

			lines = dataFile.readlines()

			for i in range(len(lines)):

				if i < len(newLines):
					newLines[i] += lines[i].strip() + " "

	with open("data.txt", "w") as data:

		for line in newLines:
			print(line, file=data)

conglomerateData(["../GUI/time.txt", "../GUI/currentReadings.txt", "../GUI/depthReadings.txt", "../GUI/forceReadings.txt"])