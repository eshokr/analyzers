import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('Demo')
process.MessageLogger.cerr.INFO = cms.untracked.PSet(
        limit = cms.untracked.int32(-1)
        )
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True),
SkipEvent = cms.untracked.vstring('ProductNotFound') )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
                                # replace 'myfile.root' with the source file you want to use
                                fileNames = cms.untracked.vstring(
# this root file is given in the link
            # https://twiki.cern.ch/twiki/bin/viewauth/CMS/CMSEgyptAnalysisSchool2015TrackingVertexingExercise
                                        
                        'file:root://cms-xrd-global.cern.ch///store/hidata/HIRun2018A/HIMinimumBias14/AOD/PromptReco-v2/000/327/211/00001/8235733E-C089-1B43-AF8D-F899602503D4.root' , ' file:root://cms-xrd-global.cern.ch///store/hidata/HIRun2018A/HIMinimumBias14/AOD/PromptReco-v2/000/327/564/00000/FE88346D-4AC2-6B48-B734-C0D27F9B1565.root' , 'file:root://cms-xrd-global.cern.ch///store/hidata/HIRun2018A/HIMinimumBias14/AOD/PromptReco-v2/000/327/564/00000/FCCC7957-BB4A-4E4E-9A08-D0981BACE795.root' ,'file:root://cms-xrd-global.cern.ch///store/hidata/HIRun2018A/HIMinimumBias14/AOD/PromptReco-v2/000/327/564/00000/F9C936AF-5B66-6246-9539-929F83BEEFB8.root' ,'file:root://cms-xrd-global.cern.ch///store/hidata/HIRun2018A/HIMinimumBias14/AOD/PromptReco-v2/000/327/564/00000/F9948DFC-B3EB-064B-8DE8-B09295424639.root'

                )
                            )

process.demo = cms.EDAnalyzer('DemoAnalyzer5',
trck = cms.InputTag("generalTracks"),
	bmspt = cms.InputTag("offlineBeamSpot"),
vrtx = cms.InputTag("offlinePrimaryVertices"),

                                         minTracks=cms.untracked.uint32(0)
                              )
process.TFileService = cms.Service("TFileService",
                                       fileName = cms.string('histograms.root')
                                   )
    
    

process.p = cms.Path(process.demo)
