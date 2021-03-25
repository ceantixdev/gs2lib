def notify(status){
	emailext (
		body: '$DEFAULT_CONTENT',
		recipientProviders: [
			[$class: 'CulpritsRecipientProvider'],
			[$class: 'DevelopersRecipientProvider'],
			[$class: 'RequesterRecipientProvider']
		],
		replyTo: '$DEFAULT_REPLYTO',
		subject: '$DEFAULT_SUBJECT',
		to: '$DEFAULT_RECIPIENTS'
	)
}

@NonCPS
def killall_jobs() {
	def jobname = env.JOB_NAME
	def buildnum = env.BUILD_NUMBER.toInteger()
	def killnums = ""
	def job = Jenkins.instance.getItemByFullName(jobname)
	def fixed_job_name = env.JOB_NAME.replace('%2F','/')

	for (build in job.builds) {
		if (!build.isBuilding()) { continue; }
		if (buildnum == build.getNumber().toInteger()) { continue; println "equals" }
		if (buildnum < build.getNumber().toInteger()) { continue; println "newer" }

		echo "Kill task = ${build}"

		killnums += "#" + build.getNumber().toInteger() + ", "

		build.doStop();
	}

	if (killnums != "") {
		discordSend description: "in favor of #${buildnum}, ignore following failed builds for ${killnums}", footer: "", link: env.BUILD_URL, result: "ABORTED", title: "Killing task(s) ${fixed_job_name} ${killnums}", webhookURL: env.GS2EMU_WEBHOOK
	}
	echo "Done killing"
}

def buildStep(dockerImage, generator, os, defines) {
	def split_job_name = env.JOB_NAME.split(/\/{1}/)
	def fixed_job_name = split_job_name[1].replace('%2F',' ')
    def fixed_os = os.replace(' ','-')
	try{
		stage("Building on \"${dockerImage}\" with \"${generator}\" for \"${os}\"...") {
			properties([pipelineTriggers([githubPush()])])
			def commondir = env.WORKSPACE + '/../' + fixed_job_name + '/'

			docker.image("${dockerImage}").inside("-u 0:0 -e BUILDER_UID=1001 -e BUILDER_GID=1001 -e BUILDER_USER=gserver -e BUILDER_GROUP=gserver") {
				sh "sudo apt update"
				sh "sudo apt install -y gcc-multilib"

				checkout scm

				if (env.CHANGE_ID) {
					echo 'Trying to build pull request'
				}

				if (!env.CHANGE_ID) {
					sh "rm -rfv publishing/deploy/gs2lib"
					sh "mkdir -p publishing/deploy/gs2lib"
				}

				sh "mkdir -p build/"
				sh "mkdir -p lib/"
				sh "sudo rm -rfv build/*"

				discordSend description: "", footer: "", link: env.BUILD_URL, result: currentBuild.result, title: "Starting ${os} build target...", webhookURL: env.GS2EMU_WEBHOOK

				dir("build") {
					sh "cmake -G\"${generator}\" ${defines} -DVER_EXTRA=\"-${fixed_os}-${fixed_job_name}\" .. || true" // Temporary fix for Windows MingW builds
					sh "cmake --build . --config Release --target package -- -j 8"

					archiveArtifacts artifacts: '*.zip,*.tar.gz,*.tgz'
				}

				discordSend description: "", footer: "", link: env.BUILD_URL, result: currentBuild.result, title: "Build ${fixed_job_name} #${env.BUILD_NUMBER} Target: ${os} DockerImage: ${dockerImage} Generator: ${generator} successful!", webhookURL: env.GS2EMU_WEBHOOK
			}
		}
	} catch(err) {
		discordSend description: "", footer: "", link: env.BUILD_URL, result: currentBuild.result, title: "Build Failed: ${fixed_job_name} #${env.BUILD_NUMBER}", webhookURL: env.GS2EMU_WEBHOOK
		currentBuild.result = 'FAILURE'
		notify('Build failed')
		throw err
	}
}

node('master') {
	killall_jobs();
	def fixed_job_name = env.JOB_NAME.replace('%2F','/');

	checkout scm;

	env.COMMIT_MSG = sh (
		script: 'git log -1 --pretty=%B ${GIT_COMMIT}',
		returnStdout: true
	).trim()

	discordSend description: "${env.COMMIT_MSG}", footer: "", link: env.BUILD_URL, result: currentBuild.currentResult, title: "Build Started: ${fixed_job_name} #${env.BUILD_NUMBER}", webhookURL: env.GS2EMU_WEBHOOK

	sh "rm -rf ./*"

	parallel (
		//'Win64-NoMySQL': {
		//	node {
		//		buildStep('dockcross/windows-static-x64:latest', 'Unix Makefiles', 'Windows x86_64 NoMySQL', "-DNOMYSQL=TRUE")
		//	}
		//},
		//'Win64': {
		//	node {
		//		buildStep('dockcross/windows-static-x64:latest', 'Unix Makefiles', 'Windows x86_64', "-DNOMYSQL=FALSE")
		//	}
		//},
		//'Linux x86_64-NoMySQL': {
		//	node {
		//		buildStep('desertbit/crossbuild:linux-x86_64', 'Unix Makefiles', 'Linux x86_64 NoMySQL', "-DNOMYSQL=TRUE")
		//	}
		//},
		'Linux x86_64': {
			node {
				buildStep('desertbit/crossbuild:linux-x86_64', 'Unix Makefiles', 'Linux x86_64', "-DNOMYSQL=FALSE")
			}
		},
		//'Linux ARMv7-NoMySQL': {
		//	node {
		//		buildStep('desertbit/crossbuild:linux-armv7', 'Unix Makefiles', 'Linux RasPi NoMySQL', '-DNOMYSQL=TRUE')
		//	}
		//},
		'Linux ARMv7': {
			node {
				buildStep('desertbit/crossbuild:linux-armv7', 'Unix Makefiles', 'Linux RasPi', '-DNOMYSQL=FALSE')
			}
		}
    )
}