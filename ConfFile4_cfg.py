import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('Demo')
process.MessageLogger.cerr.INFO = cms.untracked.PSet(
        limit = cms.untracked.int32(-1)
        )
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
                                # replace 'myfile.root' with the source file you want to use
                                fileNames = cms.untracked.vstring(
# this root file is given in the link
            # https://twiki.cern.ch/twiki/bin/viewauth/CMS/CMSEgyptAnalysisSchool2015TrackingVertexingExercise
                                        
                        'file:/afs/cern.ch/cms/Tutorials/TWIKI_DATA/TTJets_8TeV_53X.root'

                )
                            )

process.demo = cms.EDAnalyzer('DemoAnalyzer4',

                                         minTracks=cms.untracked.uint32(0)
                              )
process.TFileService = cms.Service("TFileService",
                                       fileName = cms.string('histograms.root')
                                   )
    
    

process.p = cms.Path(process.demo)
